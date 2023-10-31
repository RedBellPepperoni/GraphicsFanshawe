#pragma once
#include "BroadPhase.h"
#include "Engine/Utils/Math.h"

namespace FanshaweGameEngine
{
	namespace Physics
	{

		// A very basic algorithm to generate collision pairs for broadPhase
		// Basically brute forcing through all the Bodies

		class DefaultBroadPhase : public BroadPhase
		{
		public:

			explicit DefaultBroadPhase(const Vector3& axis = Vector3(0.0f));

			virtual ~DefaultBroadPhase();


			std::vector<CollisionPair> FindCollisionPairs(std::vector<RigidBody3D*> bodies) override;

		protected:

			Vector3 m_axis;

		};

	}
}

