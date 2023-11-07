#include "Manifold.h"
#include "Engine/Core/Physics/PhysicsEngine/RigidBody3D.h"


namespace FanshaweGameEngine
{
	namespace Physics
	{


	

		Manifold::Manifold()
			: m_bodyOne(nullptr)
			, m_bodyTwo(nullptr)
		{
		}

		Manifold::~Manifold()
		{
		}

		void Manifold::Initilize(RigidBody3D* bodyOne, RigidBody3D* bodyTwo)
		{
			m_contactCount = 0;

			m_bodyOne = bodyOne;
			m_bodyTwo = bodyTwo;
		}

		void Manifold::AddContactPoint(const Vector3& pointOnOne, const Vector3& pointOnTwo, const Vector3& contactNormal, const float& penetration)
		{
			Vector3 relativeOne = (pointOnOne - m_bodyOne->GetPosition());
			Vector3 relativeTwo = (pointOnTwo - m_bodyTwo->GetPosition());

			ContactPoint newpoint;

			newpoint.relativePosOne = relativeOne;
			newpoint.relativePosTwo = relativeTwo;
			newpoint.collisionNormal = contactNormal;
			newpoint.collisionPenetratin = penetration;
			newpoint.totalImpulsefromContact = 0.0f;
			newpoint.totalImpulsefromFriction = 0.0f;

			const float minAllowedDistanceSquared = Square(0.2f);
			bool shouldAdd = true;


			// Check if we have multiple poiunts in the same posiiotn (almost same)
			for (uint32_t index = 0; index < m_contactCount; index++)
			{
				Vector3 vectorOneTwo = m_contactPoints[index].relativePosOne - newpoint.relativePosOne;

				// get the squared magnitude of the vector
				float distanceSquared = Dot(vectorOneTwo, vectorOneTwo);
				
				// Get the point with the latgest penetreaion
				if (distanceSquared < minAllowedDistanceSquared)
				{
					if (m_contactPoints[index].collisionPenetratin > newpoint.collisionPenetratin)
					{
						std::swap(m_contactPoints[index], m_contactPoints[m_contactCount - 1]);
						m_contactCount--;
						continue;
					}
					else
					{
						shouldAdd = false;
					}
				}

			}

			if (shouldAdd)
			{
				m_contactPoints[m_contactCount] = newpoint;
				m_contactCount++;
			}

		}

		void Manifold::ApplyImpulse()
		{
			for (uint32_t index = 0; index < m_contactCount; index++)
			{
				SolveContactPoint(m_contactPoints[index]);
			}
		}

	

		RigidBody3D* Manifold::GetBodyOne() const
		{
			return m_bodyOne;
		}

		RigidBody3D* Manifold::GetBodyTwo() const
		{
			return m_bodyTwo;
		}

		void Manifold::SolveContactPoint(ContactPoint& point) const
		{
			if (m_bodyOne->m_invMass + m_bodyTwo->m_invMass == 0.0f)
			{
				return;
			}

			Vector3& relativeOne = point.relativePosOne;
			Vector3& relativeTwo = point.relativePosTwo;


			Vector3 velocityOne = m_bodyOne->GetVelocity();// Add angular studff here later if possible
			Vector3 velocityTwo = m_bodyTwo->GetVelocity();

			Vector3& normal = point.collisionNormal;
			Vector3 velocityDirection = velocityOne - velocityTwo;


			// Contact Collision Check 

			const float Mass = (m_bodyOne->m_invMass + m_bodyTwo->m_invMass);


			// Read about "Baumgarte Stabilization"

			m_bodyOne->SetVelocity(m_bodyOne->GetVelocity() + normal * m_bodyOne->m_invMass);
			m_bodyTwo->SetVelocity(m_bodyTwo->GetVelocity() - normal * m_bodyTwo->m_invMass);


			// Friction

			/*Vector3 tangent = velocityDirection - normal * Dot(velocityDirection, normal);
			float lengthTangent = Length(tangent);

			if (lengthTangent > 0.0001f)
			{
				tangent = tangent * (1.0f / lengthTangent);

				float frictionalMass = (m_bodyOne->m_invMass + m_bodyTwo->m_invMass);

				float fricOne = m_bodyOne->GetFriction() > 0.1f ? m_bodyOne->GetFriction() : 0.1f;
				float fricTwo = m_bodyTwo->GetFriction() > 0.1f ? m_bodyTwo->GetFriction() : 0.1f;

				float frictionCoeff = sqrtf(fricOne * fricTwo);

			}*/


		}

		
	}
}
