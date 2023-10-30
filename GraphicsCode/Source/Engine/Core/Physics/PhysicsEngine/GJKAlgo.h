#pragma once
#include "Engine/Core/Physics/Collision/Colliders/Collider.h"
#include "Engine/Core/Physics/Collision/ManifoldPoints.h"
#include <array>
#include <algorithm>
namespace FanshaweGameEngine
{
	namespace Physics
	{
		struct Simplex {
		public:
			
		private:
			std::array<Vector3, 4u> Points;
			size_t m_size;

		public:
			Simplex()
				: Points()
				, m_size(0)
			{
			}

			Simplex& operator=(
				std::initializer_list<Vector3> list)
			{
				for (auto v = list.begin(); v != list.end(); v++) {
					Points[std::distance(list.begin(), v)] = *v;
				}
				m_size = list.size();

				return *this;
			}

			void push_front(
				Vector3 point)
			{
				
				Points = { point, Points[0], Points[1], Points[2] };

				m_size = m_size + 1 <= 4 ? m_size : 4;
			}

			Vector3& operator[](unsigned i) { return Points[i]; }
			size_t size() const { return m_size; }

			auto begin() const { return Points.begin(); }
			auto end()   const { return Points.end() - (3 + 1u - m_size); }
		};

#ifndef GJK_EPA_MAX_ITER
#	define GJK_EPA_MAX_ITER 32
#endif


		

		bool NextSimplex(Simplex& points, Vector3& direction);
		bool Line(Simplex& points, Vector3& direction);
		bool Triangle(Simplex& points, Vector3& direction);
	    bool Tetrahedron(Simplex& points, Vector3& direction);


	
		ManifoldPoints EPA(
			const Simplex& simplex,
			Collider* colliderA, Transform* transformA,
			Collider* colliderB, Transform* transformB);

		
		
		Vector3 Support(
			Collider* colliderA, Transform* transformA,
			Collider* colliderB, Transform* transformB,
			const Vector3& direction)
		{
			return colliderA->FindFurthestPoint(transformA, direction)
				- colliderB->FindFurthestPoint(transformB, -direction);
		}

		
		bool SameDirection(
			const Vector3& direction,
			const Vector3& ao)
		{
			return Dot(direction, ao) > 0;
		}

		// For d3 EPA

		std::pair<std::vector<glm::vec4>, size_t> GetFaceNormals(
			const std::vector<glm::vec3>& polytope,
			const std::vector<size_t>& faces);

		void AddIfUniqueEdge(
			std::vector<std::pair<size_t, size_t>>& edges,
			const std::vector<size_t>& faces,
			size_t a,
			size_t b);


		std::pair<bool, Simplex> GJK(
			Collider* colliderA, Transform* transformA,
			Collider* colliderB, Transform* transformB)
		{


			Vector3 support = Support(
				colliderA, transformA,
				colliderB, transformB, Vector3(1));

			Simplex points;
			points.push_front(support);

			Vector3 direction = -support;

			size_t iterations = 0;
			while (iterations++ < GJK_EPA_MAX_ITER) {
				support = Support(
					colliderA, transformA,
					colliderB, transformB, direction);

				if (dot(support, direction) <= 0) {
					break;
				}

				points.push_front(support);

				if (NextSimplex(points, direction)) {
					return std::make_pair(true, points);
				}
			}

			return std::make_pair(false, points);
		}

	}
}


