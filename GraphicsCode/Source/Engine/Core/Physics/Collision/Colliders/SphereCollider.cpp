#include "SphereCollider.h"
#include "Engine/Core/Physics/PhysicsEngine/Rigidbody3D.h"

namespace FanshaweGameEngine
{
	namespace Physics
	{
		SphereCollider::SphereCollider()
		{
			m_type = ColliderType::SPHERE;
			SetRadius(1.0f);
		}

		SphereCollider::SphereCollider(float radius)
		{
			m_type = ColliderType::SPHERE;
			SetRadius(radius);
		}
		SphereCollider::~SphereCollider()
		{
		}

		std::vector<Vector3>& SphereCollider::GetCollisionNormals(const RigidBody3D* currentBody)
		{
			// NO need for this in sphere collision
			m_normallist.clear();
			return m_normallist;

		}
		std::vector<ColliderEdge>& SphereCollider::GetEdgeList(const RigidBody3D* currentBody)
		{
			return m_edgelist;
		}

		void SphereCollider::GetMinMaxFromAxis(const RigidBody3D* body, const Vector3& axis, Vector3* outMin, Vector3* outMax)
		{
			Matrix4 transform = body ? body->GetTransform() * m_transform : m_transform;
		
			Vector3 position = transform[3];

			if (outMin)
			{
				*outMin = position - axis * m_radius;
			}

			if (outMax)
			{
				*outMax = position + axis * m_radius;
			}


		}
		void SphereCollider::SetRadius(const float radius)
		{
			// Set the incoming radius
			m_radius = radius;

			// Set the scale
			m_transform = Math::Scale(Matrix4(1.0f), Vector3(m_radius * 2.0f));
		}

		const float SphereCollider::GetRadius() const
		{
			return m_radius;
		}
		float SphereCollider::GetSize() const
		{
			return m_radius;
		}
	}
}