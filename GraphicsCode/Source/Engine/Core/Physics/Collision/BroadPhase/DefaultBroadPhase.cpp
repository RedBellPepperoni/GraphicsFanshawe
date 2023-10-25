#include "DefaultBroadPhase.h"
#include "Engine/Core/Physics/PhysicsEngine/RigidBody3D.h"

namespace FanshaweGameEngine
{
	namespace Physics
	{
		DefaultBroadPhase::DefaultBroadPhase(const Vector3& axis)
			: m_axis(axis)
		{

		}

		DefaultBroadPhase::~DefaultBroadPhase()
		{
		}

        std::vector<CollisionPair> DefaultBroadPhase::FindCollisionPairs(std::vector<RigidBody3D*> bodies)
        {
            std::vector<CollisionPair> pairs;

            size_t count = bodies.size();

            if (count <= 0)
            {
                // no pairs found
                return pairs;
            }

            for (size_t i = 0; i < count - 1; ++i)
            {
                for (size_t j = i + 1; j < count; ++j)
                {
                    RigidBody3D* firstBody = bodies[i];
                    RigidBody3D* secondBody = bodies[j];

                    if (!firstBody->GetCollider() || !secondBody->GetCollider())
                        continue;

                    // Skip pairs of two at objects at rest
                    if (firstBody->GetIsStationary() && secondBody->GetIsStationary())
                        continue;

                    // Skip pairs of two at static objects
                    if (firstBody->GetIsStatic() && secondBody->GetIsStatic())
                        continue;

                    // Skip pairs of one static and one at rest
                    if (firstBody->GetIsStationary() && secondBody->GetIsStatic())
                        continue;

                    if (firstBody->GetIsStatic() && secondBody->GetIsStationary())
                        continue;

                    CollisionPair pair;

                    if (i < j)
                    {
                        pair.firstBody = firstBody;
                        pair.secondBody = secondBody;
                    }
                    else
                    {
                        pair.firstBody = secondBody;
                        pair.secondBody = firstBody;
                    }

                    bool duplicate = false;

                    // Loop through all the current objects 
                    for (int index = 0; index < pairs.size(); index++)
                    {
                        CollisionPair& TempPair = pairs[index];

                        if (pair.firstBody == TempPair.firstBody && pair.secondBody == TempPair.secondBody)
                        {
                            // There is a duplicate pair
                            duplicate = true;
                        }
                    }


                    if (!duplicate)
                    { // No duplicate found
                        pairs.push_back(pair);
                    }
                }


            }


            return pairs;
        }
	}
}