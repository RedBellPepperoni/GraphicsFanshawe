#pragma once
#include <vector>


namespace FanshaweGameEngine
{
	namespace Physics
	{

		class RigidBody3D;

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

			virtual std::vector<CollisionPair> FindCollisionPairs(std::vector<RigidBody3D*> bodies) = 0;

		};


	}

}
