#pragma once
#include "Engine/Core/Physics/PhysicsUtils.h"
#include "Engine/Core/ECS/Components/Transform.h"

namespace FanshaweGameEngine
{
	using Components::Transform;


	namespace Physics
	{


		class  AABB 
		{
		public:
			
			using Pointpair = std::pair<Vector3, Vector3>;

			Vector3 Min;
			Vector3 Max;

			AABB()
				: Min(FLT_MAX)
				, Max(-FLT_MAX)
			{}

			AABB(
				const Vector3& center,
				float scale
			)
				: Min(center - scale)
				, Max(center + scale) // was / 2 before might be better
			{}

			AABB(
				const Vector3& p1,
				const Vector3& p2)
			{
				*this = FromPair(Pointpair(p1, p2));
			}

			AABB(
				const Pointpair& ps)
			{
				*this = FromPair(ps);
			}

			AABB& operator=(
				const Pointpair& ps)
			{
				*this = FromPair(ps);
				return *this;
			}

			operator Pointpair() const
			{
				return Pointpair(Min, Max);
			}

			Vector3 Center() const {
				return (Min + Max) / float(2);
			}

			/*bool Intersects(
				Transform* transform,
				const AABB& other, Transform* otherTransform) const
			{
				AABB me = TransformBounds(*this, transform);
				AABB them = TransformBounds(other, otherTransform);

				for (int i = 0; i < int(_d); i++) {
					if (me.Min[i] > them.Max[i] || me.Max[i] < them.Min[i]) return false;
				}

				return true;
			}

			bool Fits(
				Transform* transform,
				const AABB& other, Transform* otherTransform) const
			{
				AABB me = TransformBounds(*this, transform);
				AABB them = TransformBounds(other, otherTransform);

				for (int i = 0; i < int(_d); i++) {
					if (me.Min[i] >= them.Min[i] || me.Max[i] <= them.Max[i]) return false;
				}

				return true;
			}*/

		private:
			

			static AABB FromPair(
				const Pointpair& ps)
			{
				const auto& [p1, p2] = ps;

				bool p1x = p1.x < p2.x;
				bool p1y = p1.y < p2.y;
				bool p1z = p1.z < p2.z;

				AABB aabb;
				aabb.Min.x = p1x ? p1.x : p2.x;
				aabb.Min.y = p1y ? p1.y : p2.y;
				aabb.Min.z = p1z ? p1.z : p2.z;
				aabb.Max.x = !p1x ? p1.x : p2.x;
				aabb.Max.y = !p1y ? p1.y : p2.y;
				aabb.Max.z = !p1z ? p1.z : p2.z;

				return aabb;
			}
		};
	}
}
