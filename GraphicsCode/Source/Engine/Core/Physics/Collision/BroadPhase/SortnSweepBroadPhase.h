#pragma once
#include "BroadPhase.h"
#include "Engine/Utils/Math.h"

namespace FanshaweGameEngine
{
	namespace Physics
	{

		class SortnSweepBroadPhase : public BroadPhase
		{
		public:

			SortnSweepBroadPhase(const Vector3& axis = Vector3(1.0f, 0.0f, 0.0f));

			virtual ~SortnSweepBroadPhase();


			Vector3 GetAxis() const;
			void SetAxis(const Vector3& newAxis);


			

			std::vector<CollisionPair> FindCollisionPairs(std::vector<SharedPtr<RigidBody3D>> bodies) override;

		protected:

			// The axis on which the Collison test is performed
			Vector3 m_axis;

			// the index of the axis on which the Collison test is performed
			int m_axisIndex;


		};
	}
}

