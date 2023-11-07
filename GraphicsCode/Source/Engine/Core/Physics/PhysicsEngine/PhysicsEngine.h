#pragma once
#include "Engine/Utils/Math.h"
#include "Engine/Core/Memory/Memory.h"
#include "Engine/Core/Physics/Collision/BroadPhase/BroadPhase.h"
#include "RigidBody3D.h"
#include "Engine/Core/ECS/EntityManager.h"
#include <vector>


namespace FanshaweGameEngine
{ 

	class Scene;


	namespace Physics
	{
		struct PhysicsStats
		{
			uint32_t rigidBodyCount;
			uint32_t collisionCount;
			uint32_t stationaryCount;
			uint32_t staticCount;
		};

		//class RigidBody3D;
		
		


		class PhysicsEngine
		{
			

		public:
			//friend class RigidBody3D;

			PhysicsEngine();
			~PhysicsEngine();


			void Init();
			void Update(const float deltatime);
			void UpdateScene(Scene* scene);

			void UpdateECSTransforms();


			const bool GetIsPaused() const;
			void SetPaused(const bool paused);

			const Vector3& GetGravity() const;
			void SetGravity(const Vector3& gravity);

			static float GetDeltaTime();

			void UpdateRigidBodyCache();


			RigidBody3D* CreateRigidBody(Entity& entity, PhysicsProperties properties);


		protected:
			
			void UpdatePhysics();

			void BroadPhaseCollision();

			void NarrowPhaseCollision();

			void UpdateAllBodies();

			void UpdateRigidBody(RigidBody3D* body) const;



		protected:

			bool m_paused = false;
			Vector3 m_gravity;
			float m_dampingFactor;


			std::vector<RigidBody3D*> m_rigidBodies{};
			std::vector<Transform*> m_transforms{};

			std::vector<CollisionPair> m_broadPhasePairs;

			SharedPtr<BroadPhase> m_broadPhaseDetection;


			PhysicsStats m_debugStats;

			static float m_physicsTimeStep;
			float m_timeStepCounter = 0.0f;

			uint8_t m_maxSubstepsPerUpdate =1;



			Scene* m_scene = nullptr;

		};
	}
}

