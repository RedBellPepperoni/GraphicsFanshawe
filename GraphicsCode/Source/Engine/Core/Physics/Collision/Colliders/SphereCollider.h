#pragma once
#include "Engine/Core/Physics/Collision/Colliders/Collider.h"

namespace FanshaweGameEngine
{
	namespace Physics
	{
		struct SphereCollider : public Collider
		{
			
			 Vector3 Center;
			 float Radius;

		public:
			SphereCollider()
				: Collider(ColliderType::SPHERE)
				, Center(0.0f)
				, Radius(1.0f)
			{
				Bounds();
			}

			SphereCollider(
				Vector3 center,
				float radius
			)
				: Collider(ColliderType::SPHERE)
				, Center(center)
				, Radius(radius)
			{
				Bounds();
			}

			Vector3 FindFurthestPoint(
				Transform* transform,
				const Vector3& direction) const override
			{
				return Center + (Vector3)transform->GetPosition()
					+ Radius * normalize(direction) * Major(transform->GetScale());
			}

			AABB CalcBounds() const
			{
				return AABB(Center, sqrt(Radius * Radius + Radius * Radius));
			}

			bool CacheIsOld() const override
			{
				return  Center != t_center
					|| Radius != t_radius;
			}

			void UpdateCache() override
			{
				t_center = Center;
				t_radius = Radius;

				Collider::UpdateCache();
			}
		private:
			Vector3 t_center;
			float t_radius;
		};
	

	}
}
