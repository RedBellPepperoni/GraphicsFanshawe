#pragma once
#include "Engine/Utils/Math.h"
#include "Engine/Core/Memory/Memory.h"
#include "Engine/Utils/UniqueId/UniqueId.h"
#include "Engine/Core/Physics/Collision/BoundingStuff/BoundingBox.h"
#include <functional>

namespace FanshaweGameEngine
{

	namespace Physics
	{

		class Collider;
		enum ColliderType : uint8_t;
		class RigidBody3D;

		//typedef  PhysicsCollisionCallback;


		struct PhysicsProperties
		{
			// World Transform stuff
			Vector3 position = Vector3(0.0f);
			Vector3 velocity = Vector3(0.0f);
			Vector3 force = Vector3(0.0f);
			
			Quaternion rotation = Quaternion();

			float mass;

			bool stationary = true;

			// Stic collider are easier to query
			bool isStatic = false;

			// The friection coeff
			float friction = 1.0f;

			// Triggers just intersect instead of Colliding
			bool isTrigger = false;

			// teh actual Collider Type
			Collider* collider = nullptr;

		};

		//typedef std::function<bool(RigidBody3D* this_obj, RigidBody3D* colliding_obj)> PhysicsCollisionCallback;
		typedef std::function<void()> PhysicsCollisionCallback;

		class RigidBody3D
		{
			//friend class PhysicsEngine;


		public:

			RigidBody3D(const PhysicsProperties& properties = PhysicsProperties());
			~RigidBody3D();

			const Vector3& GetPosition() const;
			const Vector3& GetVelocity() const;
			const Vector3& GetForce() const;

			const Quaternion& GetRotation() const;

			const Matrix4& GetTransform() const;

			const BoundingBox& GetAABB();


			BoundingBox GetBoundingBox() const;

			void SetBoundingBox(const BoundingBox& newBoundingBox);

			void UpdateModelBoundingBox();

			void SetPosition(const Vector3& newPosition);
			void SetVelocity(const Vector3& newVelocity);
			void SetForce(const Vector3& newForce);
			void SetRotation(const Quaternion& newRot);
			
			//void SetOnCollisionCallback(PhysicsCollisionCallback& callback) { m_OnCollisionCallback = callback; }
			bool OnCollisionEvent(RigidBody3D* bodyFirst, RigidBody3D* bodySecond);


			void SetCollider(Collider& collider);
			void SetCollider(ColliderType type);
			Collider* GetCollider();

			uint64_t GetUniqueId() const;

			

			bool GetIsStatic() const;
			float GetFriction() const;

			void SetFriction(float newFriction);
			void SetStatic(bool isstatic);

			bool GetIsTrigger() const;
			void SetIsTrigger(bool trigger);


			void StationaryCheck();

			void SetIsStationary(const bool stationary);
			bool GetIsStationary() const;

			void SetStationaryThreshold(float value);
			const float GetStaionaryThresholdSquared() const;

		protected:

			


			UniqueId m_Id;

			// Changing to public for easier access

		public:

			// === Basic Velocity ======
			Vector3 m_position = Vector3(0.0f);
			Vector3 m_velocity = Vector3(0.0f);
			Vector3 m_force = Vector3(0.0f);


			


			PhysicsCollisionCallback m_OnCollisionCallback;

			// ========= Rotational and angular stuff for later on
			Quaternion m_rotation = Quaternion();

			// If the object's velocity is lower than this it is said to be staionary
			float m_StationaryVelocityThresholdSquared = 0.05f;

			float velocitySum = 0.0f;

			// Check to see if a object is not acted by forces, so it doesnt need to update
			bool m_isStationary = true;

			// Static collider are easier to query
			bool m_isStatic = false;

			// The friection coeff
			float m_friction = 1.0f;

			// Triggers just intersect instead of Colliding
			bool isTrigger = false;

			// teh actual Collider Type
			Collider* m_collider = nullptr;

			float m_invMass = 0.5;

			//=== Transforms and stuff

			//(made mutable for accessing in const functions)
			mutable Matrix4 m_transform;


			//PhysicsCollisionCallback m_OnCollisionCallback;

			BoundingBox m_modelboundingBox;
			mutable BoundingBox m_aabb;


			// A small optimisation to only update transform when needed (made mutable for acceeing in const functions)
			mutable bool m_transformDirty = false;

			// Determines if the AABB needs to be updated
			bool m_AABBDirty = false;

		};

	}

}


