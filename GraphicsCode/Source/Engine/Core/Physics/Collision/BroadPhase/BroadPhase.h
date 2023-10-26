#pragma once
#include <vector>
#include "Engine/Core/Memory/Memory.h"


namespace FanshaweGameEngine
{
	namespace Physics
	{

		class RigidBody3D;

		// The pair of body that need to test for collsiosn
		struct CollisionPair
		{
			SharedPtr<RigidBody3D> firstBody;
			SharedPtr<RigidBody3D> secondBody;

		};

		class BroadPhase
		{

		public:

			virtual ~BroadPhase() = default;

			virtual std::vector<CollisionPair> FindCollisionPairs(std::vector<SharedPtr<RigidBody3D>> bodies) = 0;

		};


	}

}
