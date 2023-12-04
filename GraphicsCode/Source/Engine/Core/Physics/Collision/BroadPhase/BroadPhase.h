#pragma once
#include <vector>
#include "Engine/Core/Memory/Memory.h"
#include "Engine/Core/Physics/PhysicsEngine/RigidBody3D.h"


namespace FanshaweGameEngine
{
	namespace Physics
	{

		

		// The pair of body that need to test for collsiosn
		struct CollisionPair
		{
			RigidBody3D* firstBody;
			RigidBody3D* secondBody;

		};

		class BroadPhase
		{

		public:

			virtual ~BroadPhase() = default;

			virtual void FindCollisionPairs(RigidBody3D** bodies, uint32_t count, std::vector<CollisionPair>& collisionPairs) = 0;

			virtual void DebugDraw() = 0;

		};


	}

}
