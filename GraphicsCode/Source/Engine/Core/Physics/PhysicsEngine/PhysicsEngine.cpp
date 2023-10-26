#include "PhysicsEngine.h"
#include "Engine/Core/Scene/Scene.h"
#include "Engine/Core/ECS/Components/RigidBodyComponent.h"
#include "Engine/Core/Physics/PhysicsEngine/RigidBody3D.h"
#include "Engine/Core/ECS/Components/Transform.h"

#include "Engine/Utils/Logging/Log.h"


namespace FanshaweGameEngine
{
	using Components::RigidBodyComponent;
	using Components::Transform;

	namespace Physics
	{


		float PhysicsEngine::m_physicsTimeStep = 1.0f / 50.0f;



		PhysicsEngine::PhysicsEngine()
			: m_gravity(Vector3(0.0f, -9.81f,0.0f))
			, m_paused(true)
			, m_dampingFactor(0.999f)
			, m_broadPhaseDetection(nullptr)
			, m_rootBody(nullptr)
		{
			m_timeStepCounter = 0.0f;
			m_rigidBodies.reserve(50);
			m_broadPhasePairs.reserve(500);

		}

		PhysicsEngine::~PhysicsEngine()
		{
			m_rigidBodies.clear();
			m_broadPhasePairs.clear();
		}

		void PhysicsEngine::Init()
		{
			m_timeStepCounter = 0.0f;
			m_gravity = Vector3(0.0f, -9.81f, 0.0f);
			m_paused = true;
			m_dampingFactor = 0.999f;
			m_physicsTimeStep = 1.0f / 50.0f;
		}

		void PhysicsEngine::Update(const float deltatime, Scene* scene)
		{
			m_rigidBodies.clear();

			// Dont update if paused
			if (m_paused)
			{
				return;
			}
			
			// cache the scene registry
			entt::registry& registry = scene->GetRegistry();

			// get all the RigidBody Components from the registry
			auto rigidBodyView = registry.view<RigidBodyComponent>();


			for (entt::entity rigidbodyEntity : rigidBodyView)
			{
				//m_rigidBodies.push_back(rigidbodyEntity-)

				RigidBodyComponent& rigidBody = rigidBodyView.get<RigidBodyComponent>(rigidbodyEntity);

				// get all the rigidBodies
				m_rigidBodies.push_back(rigidBody.GetRigidBody());

			}

			if (m_rigidBodies.empty())
			{
				// nothing to Update
				return;
			}

			m_debugStats.rigidBodyCount = (uint32_t)m_rigidBodies.size();


			m_timeStepCounter += deltatime;

			for (uint32_t i = 0; (m_timeStepCounter >= m_physicsTimeStep) && i < m_maxUpdatesPerFrame; i++)
			{
				m_timeStepCounter -= m_physicsTimeStep;
				UpdatePhysics();
			}

			if (m_timeStepCounter >= m_physicsTimeStep)
			{

				LOG_WARN("Physics taking too long to run in realtime");
				m_timeStepCounter = 0;
			}
		    

		}

		void PhysicsEngine::UpdateECSTransforms(Scene* scene)
		{

			if (!scene)
			{
				// No scene , so why update anything
				return;
			}

			// Caching the Registry
			entt::registry& registry = scene->GetRegistry();

			// getting a group containing the transform and the Rigidbody components
			auto group = registry.group<RigidBodyComponent>(entt::get<Transform>);

			// Looping through all the entties in the above group
			for (entt::entity entity : group)
			{
				// cahcing both the pointers for each entity found
				const auto& [rigidComp, transform] = group.get<RigidBodyComponent, Transform>(entity);

				SharedPtr<RigidBody3D> body = rigidComp.GetRigidBody();


				if (body->GetIsStatic() && !body->GetIsStationary())
				{
					transform.SetPosition(body->GetPosition());
					transform.SetRotation(body->GetRotation());
				}

			}






		}

		const bool PhysicsEngine::GetIsPaused() const
		{
			return false;
		}

		void PhysicsEngine::SetPaused(const bool paused)
		{
		}

		const Vector3& PhysicsEngine::GetGravity() const
		{
			// TODO: insert return statement here
			return m_gravity;
		}

		void PhysicsEngine::SetGravity(const Vector3& gravity)
		{
		}

		float PhysicsEngine::GetDeltaTime()
		{
			return 0.0f;
		}

		// Initial Check to get pairs of potential collision using AABBs
		
		void PhysicsEngine::UpdatePhysics()
		{
		}

		void PhysicsEngine::BroadPhaseCollision()
		{
			// Resetting the Pair cahce
			m_broadPhasePairs.clear();

			if (!m_broadPhaseDetection)
			{
				// No BroadPhase Detector found
				return;
			}


			// get the potential Collison pairs
			m_broadPhaseDetection->FindCollisionPairs(m_rigidBodies);


		   


		}
		void PhysicsEngine::NarrowPhaseCollision()
		{
		}
		void PhysicsEngine::UpdateAllBodies()
		{
		}
		void PhysicsEngine::UpdateRigidBody(RigidBody3D* body) const
		{
		}
}
}