#pragma once
#include <vector>
#include "Engine/Utils/Math.h"
#include "Engine/Core/Memory/Memory.h"
#include "Engine/Utils/Singleton.h"


namespace FanshaweGameEngine
{
	namespace Physics
	{
		class RigidBody3D;
		class Collider;
		class SphereCollider;
		class MeshCollider;



		struct CollisionData
		{
			float penetration;

			Vector3 collisionNormal;
			Vector3 pointOnPlane;
		};

		class NarrowPhase : public Singleton<NarrowPhase>
		{
		private:

			// making the binary value to the fill all the values with 1
			// right now max colliders is 32 (10000) so making it 63 which is (11111)

			int m_MaxType = 0;


		public:

			NarrowPhase();
			~NarrowPhase();


			bool DetectCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo, Collider* colliderOne, Collider* colliderTwo, CollisionData* outData);


protected:

		    static bool CheckCollisionbySAT(const Vector3& axis, RigidBody3D* bodyOne, RigidBody3D* bodyTwo, SphereCollider* colliderOne, SphereCollider* colliderTwo, CollisionData* outData);

			bool DetectSphereCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo, SphereCollider* colliderOne, SphereCollider* colliderTwo, CollisionData* outData);
			//bool DetectBoxCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo, SphereCollider* colliderOne, SphereCollider* colliderTwo, CollisionData* outData)

		
			bool DetectSphereMeshCollision(RigidBody3D* bodyOne, RigidBody3D* bodyTwo, SphereCollider* colliderOne, MeshCollider* colliderTwo, CollisionData* outData);
		};
	}
}
