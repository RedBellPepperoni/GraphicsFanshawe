#include "PhysicsEngine.h"
#include "Engine/Core/Scene/Scene.h"
#include "Engine/Core/ECS/Components/RigidBodyComponent.h"
#include "Engine/Core/Physics/PhysicsEngine/RigidBody3D.h"
#include "Engine/Core/ECS/Components/Transform.h"
#include "Engine/Core/Physics/Collision/Broadphase/OctreeBroadPhase.h"
#include "Engine/Core/Physics/Collision/Broadphase/DefaultBroadPhase.h"
#include "Engine/Core/Physics/Collision/NarrowPhase/NarrowPhase.h"
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
			
		{
			m_timeStepCounter = 0.0f;
			//m_rigidBodies.reserve(50);
			//m_broadPhasePairs.reserve(500);

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
			//m_gravity = Vector3(0.0f, 0.0f, 0.0f);
			m_paused = true;
			m_dampingFactor = 0.98f;
			m_physicsTimeStep = 1.0f / 50.0f;
			//m_broadPhaseDetection = MakeShared<DefaultBroadPhase>();
			m_broadPhaseDetection = MakeShared<OctreeBroadPhase>(5,5,MakeShared<DefaultBroadPhase>());
			
		}

		void PhysicsEngine::Update(const float deltatime)
		{
			//m_rigidBodies.clear();

			// Dont update if paused
			if (m_paused)
			{
				return;
			}
			
			

			if (m_rigidBodies.empty())
			{
				// nothing to Update
				return;
			}

			


			m_debugStats.rigidBodyCount = (uint32_t)m_rigidBodies.size();
			
			m_timeStepCounter += deltatime;

			for (uint32_t i = 0; (m_timeStepCounter >= m_physicsTimeStep) && (i < m_maxSubstepsPerUpdate); i++)
			{
				m_timeStepCounter -= m_physicsTimeStep;
				UpdatePhysics();
			}

			if (m_timeStepCounter > m_physicsTimeStep)
			{

				LOG_WARN("Physics taking too long to run in realtime");
				m_timeStepCounter = 0;
			}
		    

		}

		void PhysicsEngine::UpdateScene(Scene* scene)
		{
			m_scene = scene;
		}

		void PhysicsEngine::UpdateECSTransforms()
		{

			if (!m_scene)
			{
				// No scene , so why update anything
				return;
			}


			if(m_transforms.empty() || m_rigidBodies.empty())
			{
				return;
			}


			// Optimised this step by a lot
			for (int index = 0; index < m_transforms.size(); index ++)
			{
				RigidBody3D* body = m_rigidBodies[index];

				if (!body->GetIsStatic() && !body->GetIsStationary())
				{
					m_transforms[index]->SetPosition(body->GetPosition());

					

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
			return m_physicsTimeStep;
		}

		// Call this when you create or Delete a rigidbody
		void PhysicsEngine::UpdateRigidBodyCache()
		{

			//m_rigidBodies.clear();

			if (!m_scene)
			{
				return;
			}

			ComponentView<RigidBody3D> rigidBodyView = m_scene->GetEntityManager()->GetComponentsOfType<RigidBody3D>();


			for (Entity rigidbodyEntity : rigidBodyView)
			{			

				RigidBody3D* rigidBody = &rigidbodyEntity.GetComponent<RigidBody3D>();
				Transform* transform = &rigidbodyEntity.GetComponent<Transform>();

				// get all the rigidBodies
				m_rigidBodies.push_back(rigidBody);
				m_transforms.push_back(transform);

			}

			

		}

		RigidBody3D* PhysicsEngine::CreateRigidBody(Entity& entity, PhysicsProperties properties)
		{

			RigidBody3D* body = &entity.AddComponent<RigidBody3D>(properties);
			Transform* transform = &entity.AddComponent<Transform>();

			body->SetPosition(properties.position);

			transform->SetPosition(properties.position);
			transform->SetRotation(properties.rotation);
			transform->SetScale(Vector3(1.0f));

			if (!m_rigidBodies.empty())
			{
				m_rigidBodies.clear();
				m_transforms.clear();
			}

			UpdateRigidBodyCache();

			return body;
		}


		void PhysicsEngine::DebugDraw()
		{
			if (m_paused)
			{
				return;
			}

			//m_broadPhaseDetection->DebugDraw();
			

			for (RigidBody3D* body : m_rigidBodies)
			{
				body->DebugDraw(0);

				SharedPtr<Collider> collider = body->GetCollider();

				if (collider)
				{
					collider->DebugDraw(body);
				}
			}

		}

		

	

		// Initial Check to get pairs of potential collision using AABBs
		
		void PhysicsEngine::UpdatePhysics()
		{

			m_manifoldList.clear();

			BroadPhaseCollision();

			NarrowPhaseCollision();

			SolveManifolds();

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

			
			m_rigidBodies;

			// get the potential Collison pairs
			m_broadPhaseDetection->FindCollisionPairs(m_rigidBodies.data(), (uint32_t)m_rigidBodies.size(), m_broadPhasePairs);

		

		

		}
		void PhysicsEngine::NarrowPhaseCollision()
		{
			if(m_broadPhasePairs.empty())
			{
				return;
			}


			//LOG_CRITICAL("NarrowPhasePairs : {0}", m_broadPhasePairs.size());

			for (CollisionPair& pair : m_broadPhasePairs)
			{
				Collider* colliderOne = pair.firstBody->GetCollider().get();
				Collider* colliderTwo = pair.secondBody->GetCollider().get();


				if (colliderOne && colliderTwo)
				{
					CollisionData coldata;


					if (NarrowPhase::GetInstance().DetectCollision(pair.firstBody, pair.secondBody, colliderOne, colliderTwo, &coldata))
					{
						//const bool callfirst = pair.firstBody->OnCollisionEvent(pair.firstBody, pair.secondBody);
						//const bool callSecond = pair.secondBody->OnCollisionEvent(pair.secondBody, pair.firstBody);


						

						//if (callfirst && callSecond)
						if (true)
						{

							m_manifoldLock.lock();
							Manifold& manifold = m_manifoldList.emplace_back();
							manifold.Initilize(pair.firstBody, pair.secondBody);

							if (NarrowPhase::GetInstance().BuildCollisionManifold(pair.firstBody, pair.secondBody, colliderOne, colliderTwo, coldata, &manifold))
							{
								pair.firstBody->OnCollisionManifoldCallback(pair.firstBody, pair.secondBody, &manifold);
								pair.secondBody->OnCollisionManifoldCallback(pair.firstBody, pair.secondBody, &manifold);

								m_debugStats.collisionCount++;

								
							}

							else
							{
								m_manifoldList.pop_back();
							}


							m_manifoldLock.unlock();

						}


						

					}

				}

			}



			

		}


		void PhysicsEngine::UpdateAllBodies()
		{

			m_debugStats.staticCount = 0;
			m_debugStats.stationaryCount = 0;
			m_debugStats.rigidBodyCount = 0;


			for (RigidBody3D* body : m_rigidBodies)
			{
				UpdateRigidBody(body);

				m_debugStats.rigidBodyCount++;

				// make it stationary if the velocity is too low
				body->StationaryCheck();
			}


			m_debugStats.rigidBodyCount;

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

			m_physicsTimeStep *= m_positionIterations;

		}

		void PhysicsEngine::SolveManifolds()
		{
			for (Manifold& manifold : m_manifoldList)
			{
				manifold.SolveElasticity(m_physicsTimeStep);
				
			}


			for (uint32_t i = 0; i < m_velocityIterations; i++)
			{
				for (Manifold& manifold : m_manifoldList)
				{
					manifold.ApplyImpulse();
				}
			}

		}
	}
}