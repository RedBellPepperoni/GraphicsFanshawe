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

		bool NarrowPhase::CheckCollisionbySAT(const Vector3& axis, RigidBody3D* bodyOne, RigidBody3D* bodyTwo, SphereCollider* colliderOne, SphereCollider* colliderTwo, CollisionData* outData)
		{
			Vector3 minOne, maxOne;
			Vector3 minTwo, maxTwo;

			colliderOne->GetMinMaxFromAxis(bodyOne, axis, &minOne, &maxOne);
			colliderOne->GetMinMaxFromAxis(bodyTwo, axis, &minTwo, &maxTwo);

			float minOneCorrelation = Dot(axis, minOne);
			float maxOneCorrelation = Dot(axis, maxOne);
			float minTwoCorrelation = Dot(axis, minTwo);
			float maxTwoCorrelation = Dot(axis, maxTwo);

			if (minOneCorrelation < minTwoCorrelation && maxOneCorrelation >= minTwoCorrelation)
			{
				if (outData != nullptr)
				{
					outData->collisionNormal = axis;
					outData->penetration = minTwoCorrelation - maxOneCorrelation;
					outData->pointOnPlane = maxOne + outData->collisionNormal * outData->penetration;
				}

				return true;

			}

			if (minTwoCorrelation <= minOneCorrelation && maxTwoCorrelation > minOneCorrelation)
			{
				if (outData != nullptr)
				{
					outData->collisionNormal = -axis;
					outData->penetration = minOneCorrelation - maxTwoCorrelation;
					outData->pointOnPlane = minOne + outData->collisionNormal * outData->penetration;
				}

				return true;

			}

			return false;
		}

		bool NarrowPhase::DetectSphereCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo, SphereCollider* colliderOne, SphereCollider* colliderTwo, CollisionData* outData)
		{
			CollisionData data;

			Vector3 axis = bodyTwo->GetPosition() - bodyOne->GetPosition();
			axis = Normalize(axis);

			if (!CheckCollisionbySAT(axis, bodyOne, bodyTwo, colliderOne, colliderTwo, &data));
			{
				return false;
			}

			if (outData)
			{
				*outData = data;
			}

			return true;
		}




	}
}