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
			m_transform = Math::Scale(Matrix4(1.0f), Vector3(m_radius * 2.0f));
		}

		SphereCollider::SphereCollider(float radius)
		{
			m_type = ColliderType::SPHERE;
			SetRadius(radius);
			m_transform = Math::Scale(Matrix4(1.0f), Vector3(m_radius * 2.0f));
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

		void SphereCollider::GetManifoldPolygon(const RigidBody3D* currentObject, const Vector3& axis, ManifoldPolygon& manifoldPolygon) const
		{
			// Since its a sphere, we only need one face that will be parallel

			manifoldPolygon.Faces[0] = currentObject->GetPosition() + axis * m_radius;
			manifoldPolygon.FaceCount = 1;

			manifoldPolygon.Normal = axis;
		}

		Matrix3 SphereCollider::BuildInverseInertia(float invMass) const
		{

		//https://en.wikipedia.org/wiki/List_of_moments_of_inertia
			// SOLID
			float i = 2.5f * invMass / (m_radius * m_radius);
			

			Matrix3 inertia;
			inertia[0][0] = i;
			inertia[1][1] = i;
			inertia[2][2] = i;

			return inertia;
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