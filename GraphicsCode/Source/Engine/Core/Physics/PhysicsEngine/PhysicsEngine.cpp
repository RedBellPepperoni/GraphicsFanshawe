#include "PhysicsEngine.h"
#include "Engine/Core/Scene/Scene.h"
#include "Engine/Core/ECS/Components/RigidBodyComponent.h"
#include "Engine/Core/Physics/PhysicsEngine/RigidBody3D.h"
#include "Engine/Core/ECS/Components/Transform.h"
#include "Engine/Core/Physics/Collision/Broadphase/SortnSweepBroadPhase.h"
#include "Engine/Core/Physics/Collision/Broadphase/DefaultBroadPhase.h"
#include "Engine/Core/Physics/Collision/NarrowPhase/NarrowPhase.h"
#include "Engine/Utils/Logging/Log.h"


namespace FanshaweGameEngine
{
	using Components::RigidBodyComponent;
	using Components::Transform;

	namespace Physics
	{


		float PhysicsEngine::m_physicsTimeStep = 1.0f / 30.0f;



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
			//m_gravity = Vector3(0.0f, -9.81f, 0.0f);
			m_gravity = Vector3(0.0f, 0.0f, 0.0f);
			m_paused = true;
			m_dampingFactor = 0.98f;
			m_physicsTimeStep = 1.0f / 30.0f;

			m_broadPhaseDetection = MakeShared<DefaultBroadPhase>();
			//m_broadPhaseDetection = MakeShared<SortnSweepBroadPhase>();
		}

		void PhysicsEngine::Update(const float deltatime, Scene* scene)
		{
			m_rigidBodies.clear();

			// Dont update if paused
			if (m_paused)
			{
				return;
			}
			
			ComponentView<RigidBody3D> rigidBodyView = scene->GetEntityManager()->GetComponentsOfType<RigidBody3D>();


			for (Entity rigidbodyEntity : rigidBodyView)
			{
				//m_rigidBodies.push_back(rigidbodyEntity-)

				RigidBody3D* rigidBody = &rigidbodyEntity.GetComponent<RigidBody3D>();

				// get all the rigidBodies
				m_rigidBodies.push_back(rigidBody);

			}

			if (m_rigidBodies.empty())
			{
				// nothing to Update
				return;
			}

			m_debugStats.rigidBodyCount = (uint32_t)m_rigidBodies.size();

			//LOG_WARN("Nodies : {0}", m_debugStats.rigidBodyCount);


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

			ComponentView<RigidBody3D> rigidBodyView = scene->GetEntityManager()->GetComponentsOfType<RigidBody3D>();


			
			for (Entity rigidbodyEntity : rigidBodyView)
			{
				

				RigidBody3D* rigidBody = &rigidbodyEntity.GetComponent<RigidBody3D>();

				if (!rigidBody->GetIsStatic() && !rigidBody->GetIsStationary())
				{
					Transform* transform = &rigidbodyEntity.GetComponent<Transform>();

					transform->SetPosition(rigidBody->GetPosition());
					//transform->SetRotation(rigidBody->GetRotation());

				}

				


			}
		






		}

		const bool PhysicsEngine::GetIsPaused() const
		{
			return m_paused;
		}

		void PhysicsEngine::SetPaused(const bool paused)
		{
			m_paused = paused;
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

			BroadPhaseCollision();

			NarrowPhaseCollision();

			UpdateAllBodies();



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
			m_broadPhasePairs = m_broadPhaseDetection->FindCollisionPairs(m_rigidBodies);

			
			for (CollisionPair& pair : m_broadPhasePairs)
			{
				Collider* colliderOne = pair.firstBody->GetCollider();
				Collider* colliderTwo = pair.secondBody->GetCollider();


				if (colliderOne && colliderTwo)
				{
					CollisionData coldata;


					if (NarrowPhase::Get().DetectCollision(pair.firstBody, pair.secondBody, colliderOne, colliderTwo, &coldata))
					{
						const bool callfirst = pair.firstBody->OnCollisionEvent(pair.firstBody, pair.secondBody);
						const bool callSecond = pair.secondBody->OnCollisionEvent(pair.secondBody, pair.firstBody);

					}

				}

			}
		   


		}
		void PhysicsEngine::NarrowPhaseCollision()
		{
			if(m_broadPhasePairs.empty())
			{
				return;
			}


			m_debugStats.collisionCount = 0;

		}
		void PhysicsEngine::UpdateAllBodies()
		{

			m_debugStats.staticCount = 0;
			m_debugStats.stationaryCount = 0;
			m_debugStats.rigidBodyCount = 0;


			for (RigidBody3D* body : m_rigidBodies)
			{
				UpdateRigidBody(body);
			}


		}
		void PhysicsEngine::UpdateRigidBody(RigidBody3D* body) const
		{
			if (!body->GetIsStatic() && !body->GetIsStationary())
			{
				

				const float damping = m_dampingFactor;

				// Apply gravity
				if (body->m_invMass > 0.0f)
				{
					body->m_velocity += m_gravity * m_physicsTimeStep;
				}

				//LOG_WARN("Body Velo  {0} {1} {2}", body->m_velocity.x, body->m_velocity.y, body->m_velocity.z);
				
					// Update position
					body->m_position += body->m_velocity * m_physicsTimeStep;

					// Update linear velocity (v = u + at)
					body->m_velocity += body->m_force * body->m_invMass * m_physicsTimeStep;

					// Linear velocity damping
					body->m_velocity = body->m_velocity * damping;

					
					// No rotation for now
				
				
				// Mark cached world transform and AABB as invalid
				body->m_AABBDirty = true;
				body->m_transformDirty = true;
			}

		}
}
}