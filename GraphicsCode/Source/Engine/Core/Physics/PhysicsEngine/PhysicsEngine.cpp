#include "PhysicsEngine.h"
#include "Engine/Core/Scene/Scene.h"
#include "Engine/Core/ECS/Components/RigidBodyComponent.h"
#include "Engine/Core/Physics/PhysicsEngine/RigidBody3D.h"

namespace FanshaweGameEngine
{
	using Components::RigidBodyComponent;

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
			

			//if()


			entt::registry& registry = scene->GetRegistry();

			auto rigidBodyView = registry.view<RigidBodyComponent>();


			for (entt::entity rigidbodyEntity : rigidBodyView)
			{
				//m_rigidBodies.push_back(rigidbodyEntity-)

				RigidBodyComponent& rigidBody = rigidBodyView.get<RigidBodyComponent>(rigidbodyEntity);

				// get all the rigidBodies
				m_rigidBodies.push_back( rigidBody.GetRigidBody());

			}

			if (m_rigidBodies.empty())
			{
				// nothing to Update
				return;
			}

			m_debugStats.rigidBodyCount = (uint32_t)m_rigidBodies.size();




		}
	}
}