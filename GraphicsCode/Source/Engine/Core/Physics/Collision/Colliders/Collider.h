#pragma once
#include "Engine/Core/Physics/Collision/Bounds/AABB.h"
#include <vector>

namespace FanshaweGameEngine
{
	namespace Physics
	{
		enum class ColliderType 
		{
			PLANE,
			SPHERE,
			CAPSULE,
			HULL,
			MESH
		};
		

		struct ColliderBase;	
		struct Collider;


		struct ColliderBase 
		{
			const ColliderType m_type;
			

			ColliderBase(ColliderType type)
				: m_type(type)	
			{}

			template<typename _t>
			_t* as() {
				assert(_t().get_id() == get_id());
				return (_t*)this;
			}

			size_t get_id() const {
				return (size_t)m_type;
			}

			virtual bool CacheIsOld() const = 0;
			virtual void UpdateCache() = 0;
		};

		
		struct Collider: ColliderBase
		{
					

			Collider(ColliderType type)
				: ColliderBase(type)
			{
				
			}

			virtual Vector3 FindFurthestPoint(
				Transform* transform,
				const Vector3& direction) const = 0;

			virtual AABB CalcBounds() const = 0;

			AABB Bounds()
			{
				if (CacheIsOld())
				{
					UpdateCache();
				}

				return m_bounds;
			}

			void UpdateCache() override
			{
				m_bounds = CalcBounds();
			}
		private:
			AABB m_bounds;
		};

	}
}

