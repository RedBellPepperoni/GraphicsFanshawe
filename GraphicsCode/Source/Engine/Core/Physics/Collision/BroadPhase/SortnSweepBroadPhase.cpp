#include "SortnSweepBroadPhase.h"
#include <algorithm>
#include "Engine/Core/Physics/PhysicsEngine/RigidBody3D.h"
#include "Engine/Utils/Logging/Log.h"

namespace FanshaweGameEngine
{
	namespace Physics
	{
		SortnSweepBroadPhase::SortnSweepBroadPhase(const Vector3& axis)
			: m_axisIndex(0)
		{
			SetAxis(axis);
		}

		SortnSweepBroadPhase::~SortnSweepBroadPhase()
		{
			
		}
		Vector3 SortnSweepBroadPhase::GetAxis() const
		{
			return m_axis;
		}

		void SortnSweepBroadPhase::SetAxis(const Vector3& newAxis)
		{
			m_axis = newAxis;

			Normalize(m_axis);

			if (Abs(m_axis.x) > 0.9f)
			{
				m_axisIndex = 0;
			}

			else if (Abs(m_axis.y) > 0.9f)
			{
				m_axisIndex = 1;
			}
			
			else if (Abs(m_axis.z) > 0.9f)
			{
				m_axisIndex = 2;
			}


		}


		


		std::vector<CollisionPair> SortnSweepBroadPhase::FindCollisionPairs( std::vector<RigidBody3D*> bodies)
		{
			std::vector<CollisionPair> pairs;

			size_t count = bodies.size();

			// TODO: insert return statement here
			 // Sort entities along axis
			// Sort entities along axis
			std::sort(bodies.data(), bodies.data() + count, [this](RigidBody3D* a, RigidBody3D* b) -> bool
				{ return a->GetAABB().Min()[this->m_axisIndex] < b->GetAABB().Min()[this->m_axisIndex]; });

			for (uint32_t i = 0; i < count; i++)
			{
				RigidBody3D& firstBody = *bodies[i];

				float thisBoxRight = firstBody.GetAABB().Max()[m_axisIndex];

				for (uint32_t iit = i + 1; iit < count; iit++)
				{
					RigidBody3D& secondBody = *bodies[iit];
					// Skip pairs of two at rest/static objects
					if (firstBody.GetIsStationary() && secondBody.GetIsStationary())
						continue;

					// Skip pairs of two at static objects
					if (firstBody.GetIsStatic() && secondBody.GetIsStatic())
						continue;

					// Skip pairs of one static and one at rest
					if (firstBody.GetIsStationary() && secondBody.GetIsStatic())
						continue;

					if (firstBody.GetIsStatic() && secondBody.GetIsStationary())
						continue;

					float testBoxLeft = secondBody.GetAABB().Min()[m_axisIndex];

					// Test for overlap between the axis values of the bounding boxes
					if (testBoxLeft < thisBoxRight)
					{
						CollisionPair pair;
						pair.firstBody = &firstBody;
						pair.secondBody = &secondBody;

						pairs.push_back(pair);

						LOG_INFO("Yeet");
						
					}
				}
			}

			LOG_INFO("Count: {0}", pairs.size());
			// Implement this later
			return pairs;
			
		}
	}
}