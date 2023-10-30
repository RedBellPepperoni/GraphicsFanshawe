#pragma once
#include "Collider.h"

namespace FanshaweGameEngine
{
	namespace Physics
	{
		struct PlaneCollider : public Collider
		{
			

			Vector3 Normal;
			float Distance;

			PlaneCollider()
				: Collider(ColliderType::PLANE)
				, Normal(0)
				, Distance(0)
			{
				Normal[1] = 1; // y = 1 as default
				Bounds();
			}

			PlaneCollider(
				Vector3 normal,
				float distance
			)
				: Collider(ColliderType::PLANE)
				, Normal(normal)
				, Distance(distance)
			{
				Bounds();
			}

			Vector3 FindFurthestPoint(
				Transform* transform,
				const Vector3& direction) const override
			{
				return Vector3(0);
			}

			AABB CalcBounds() const
			{
				// could calc actual bounds but ill wait till
				// i need a non infinite plane

				return AABB();
			}

			bool CacheIsOld() const override
			{
				return  Normal != t_normal
					|| Distance != t_distance;
			}

			void UpdateCache() override
			{
				t_normal = Normal;
				t_distance = Distance;

				Collider::UpdateCache();
			}
		private:
			Vector3 t_normal;
			float t_distance;
		};

		
	}
}
