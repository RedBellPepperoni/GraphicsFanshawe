#include "SortnSweepBroadPhase.h"
#include <algorithm>
#include "Engine/Core/Physics/PhysicsEngine/RigidBody3D.h"

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


		


		std::vector<CollisionPair> SortnSweepBroadPhase::FindCollisionPairs(std::vector<SharedPtr<RigidBody3D>> bodies)
		{
			// TODO: insert return statement here
			 // Sort entities along axis


			// Implement this later
			return std::vector<CollisionPair>();
			
		}
	}
}