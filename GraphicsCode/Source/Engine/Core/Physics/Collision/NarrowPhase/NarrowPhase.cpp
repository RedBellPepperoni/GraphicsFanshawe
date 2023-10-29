#pragma once
#include "NarrowPhase.h"
#include "Engine/Core/Physics/PhysicsEngine/RigidBody3D.h"
#include "Engine/Core/Physics/Collision/Colliders/Collider.h"
#include "Engine/Core/Physics/Collision/Colliders/SphereCollider.h"
#include "Engine/Core/Physics/Collision/Colliders/MeshCollider.h"
#include "Engine/Utils/Logging/Log.h"


namespace FanshaweGameEngine
{
	namespace Physics
	{

		


		NarrowPhase::NarrowPhase()
		{
			m_MaxType = (ColliderType::MAX | (ColliderType::MAX >> 1));
		}

		NarrowPhase::~NarrowPhase()
		{
		}

		bool NarrowPhase::DetectCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo, Collider* colliderOne, Collider* colliderTwo, CollisionData* outData)
		{
			// caching the types for faster computation
			ColliderType typeOne = colliderOne->GetType();
			ColliderType typeTwo = colliderTwo->GetType();

			if ((typeOne | typeTwo) > m_MaxType)
			{
				LOG_ERROR("INVALID Collider : {0} {1}", std::to_string(typeOne), std::to_string(typeTwo));
			}


			// Check Sphere Sphere First
			
			if (typeOne == ColliderType::SPHERE && typeTwo == ColliderType::SPHERE)
			{
				// Reverse casting cuz its fun :(
				// This will Break a lot of stuff if teh casts are wrong
				return DetectSphereCollision(bodyOne, bodyTwo, (SphereCollider*)&colliderOne, (SphereCollider*)&colliderTwo, outData);
			}


			return false;
		}

		bool NarrowPhase::DetectSphereCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo, SphereCollider* colliderOne, SphereCollider* colliderTwo, CollisionData* outData)
		{



			return false;
		}




	}
}