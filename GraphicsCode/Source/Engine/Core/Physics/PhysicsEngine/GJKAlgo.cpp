#include "GJKAlgo.h"

namespace FanshaweGameEngine
{
	namespace Physics
	{
		
		bool NextSimplex(
			Simplex& points,
			Vector3& direction)
		{
			switch (points.size()) {
			case 2: return Line(points, direction);
			case 3: return Triangle(points, direction);
			case 4: return Tetrahedron(points, direction);
			}

			// never should be here
			return false;
		}

		
		

		bool Line(
			Simplex& points,
			Vector3& direction)
		{
			

			Vector3 a = points[0];
			Vector3 b = points[1];

			Vector3 ab = b - a;
			Vector3 ao = -a;

			if (SameDirection(ab, ao)) {
				direction = Cross(Cross(ab, ao), ab);
			}

			else {
				points = { a };
				direction = ao;
			}

			return false;
		}

		
		bool Triangle(
			Simplex& points,
			Vector3& direction)
		{
			

			Vector3 a = points[0];
			Vector3 b = points[1];
			Vector3 c = points[2];

			Vector3 ab = b - a;
			Vector3 ac = c - a;
			Vector3 ao = -a;

			Vector3 abc = Cross(ab, ac);

			if (SameDirection(Cross(abc, ac), ao)) {
				if (SameDirection(ac, ao)) {
					points = { a, c };
					direction = Cross(Cross(ac, ao), ac);
				}

				else {
					return Line(points = { a, b }, direction);
				}
			}

			else {
				if (SameDirection(Cross(ab, abc), ao)) {
					return Line(points = { a, b }, direction);
				}

				else {
					if (SameDirection(abc, ao)) {
						direction = abc;
					}

					else {
						points = { a, c, b };
						direction = -abc;
					}
				}
			}

			return false;
		}

		
		bool Tetrahedron(
			Simplex& points,
			Vector3& direction)
		{
			

			Vector3 a = points[0];
			Vector3 b = points[1];
			Vector3 c = points[2];
			Vector3 d = points[3];

			Vector3 ab = b - a;
			Vector3 ac = c - a;
			Vector3 ad = d - a;
			Vector3 ao = -a;

			Vector3 abc = Cross(ab, ac);
			Vector3 acd = Cross(ac, ad);
			Vector3 adb = Cross(ad, ab);

			if (SameDirection(abc, ao)) return Triangle(points = { a, b, c }, direction);
			if (SameDirection(acd, ao)) return Triangle(points = { a, c, d }, direction);
			if (SameDirection(adb, ao)) return Triangle(points = { a, d, b }, direction);

			return true;
		}

		ManifoldPoints EPA(
			const Simplex& simplex,
			Collider* colliderA, Transform* transformA,
			Collider* colliderB, Transform* transformB)
		{
			

			std::vector<Vector3> polytope(simplex.begin(), simplex.end());
			std::vector<size_t>  faces = {
				0, 1, 2,
				0, 3, 1,
				0, 2, 3,
				1, 3, 2
			};

			auto [normals, minFace] = GetFaceNormals(polytope, faces);

			Vector3 minNormal;
			float minDistance = FLT_MAX;

			size_t iterations = 0;
			while (minDistance == FLT_MAX)
			{
				minNormal = Vector3(normals[minFace]);
				minDistance = normals[minFace].w;

				if (iterations++ > GJK_EPA_MAX_ITER) {
					break;
				}

				Vector3 support = Support(colliderA, transformA, colliderB, transformB, minNormal);
				float sDistance = Dot(minNormal, support);

				if (abs(sDistance - minDistance) > 0.001f) {
					minDistance = FLT_MAX;

					std::vector<std::pair<size_t, size_t>> uniqueEdges;

					for (size_t i = 0; i < normals.size(); i++) {
						if (SameDirection(Vector3(normals[i]), support)) {
							size_t f = i * 3;

							AddIfUniqueEdge(uniqueEdges, faces, f, f + 1);
							AddIfUniqueEdge(uniqueEdges, faces, f + 1, f + 2);
							AddIfUniqueEdge(uniqueEdges, faces, f + 2, f);

							faces[f + 2] = faces.back(); faces.pop_back();
							faces[f + 1] = faces.back(); faces.pop_back();
							faces[f] = faces.back(); faces.pop_back();

							normals[i] = normals.back(); normals.pop_back();

							i--;
						}
					}

					if (uniqueEdges.size() == 0) {
						break;
					}

					std::vector<size_t> newFaces;
					for (auto [edge1, edge2] : uniqueEdges) {
						newFaces.push_back(edge1);
						newFaces.push_back(edge2);
						newFaces.push_back(polytope.size());
					}

					polytope.push_back(support);

					auto [newNormals, newMinFace] = GetFaceNormals(polytope, newFaces);

					float newMinDistance = FLT_MAX;
					for (size_t i = 0; i < normals.size(); i++) {
						if (normals[i].w < newMinDistance) {
							newMinDistance = normals[i].w;
							minFace = i;
						}
					}

					if (newNormals[newMinFace].w < newMinDistance) {
						minFace = newMinFace + normals.size();
					}

					faces.insert(faces.end(), newFaces.begin(), newFaces.end());
					normals.insert(normals.end(), newNormals.begin(), newNormals.end());
				}
			}

			if (minDistance == FLT_MAX) {
				return {};
			}

			ManifoldPoints points;

			points.Normal = minNormal;
			points.Depth = minDistance + 0.001f;
			points.HasCollision = true;

			return points;
		}

		std::pair<std::vector<Vector4>, size_t> GetFaceNormals(
			const std::vector<Vector3>& polytope,
			const std::vector<size_t>& faces)
		{
			std::vector<Vector4> normals;
			size_t minTriangle = 0;
			float  minDistance = FLT_MAX;

			for (size_t i = 0; i < faces.size(); i += 3) {
				Vector3 a = polytope[faces[i]];
				Vector3 b = polytope[faces[i + 1]];
				Vector3 c = polytope[faces[i + 2]];

				Vector3 normal = glm::normalize(glm::cross(b - a, c - a));
				float distance = glm::dot(normal, a);

				if (distance < 0) {
					normal *= -1;
					distance *= -1;
				}

				normals.emplace_back(normal, distance);

				if (distance < minDistance) {
					minTriangle = i / 3;
					minDistance = distance;
				}
			}

			return { normals, minTriangle };
		}

		void AddIfUniqueEdge(
			std::vector<std::pair<size_t, size_t>>& edges,
			const std::vector<size_t>& faces,
			size_t a,
			size_t b)
		{
			auto reverse = std::find(             
				edges.begin(),                    
				edges.end(),                       
				std::make_pair(faces[b], faces[a]) 
			);

			if (reverse != edges.end()) {
				edges.erase(reverse);
			}

			else {
				edges.emplace_back(faces[a], faces[b]);
			}
		}

	}
}
