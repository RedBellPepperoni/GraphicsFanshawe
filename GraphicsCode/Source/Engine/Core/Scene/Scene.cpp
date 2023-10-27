#include "Scene.h"
#include "Engine/Core/ECS/Components/ComponentDefinitions.h"
#include "Engine/Core/System/Input/FlyCameraController.h"
// Forward Declarations includes
#include "Engine/Core/ECS/EntityManager.h"
#include "Engine/Core/System/Input/inputSystem.h"



namespace FanshaweGameEngine
{

	Scene::Scene(const std::string& name)
	{
		// Setting up a new Entity Manager with the current scene's Reference
		m_EntityManager = MakeUnique<EntityManager>(this);


	//	m_EntityManager->AddDependency<Camera, Components::Transform>();
		//m_EntityManager->AddDependency<Components::MeshComponent, Components::Transform>();

	}
	Scene::~Scene()
	{
		// Cleanup the manager
		m_EntityManager->Clear();
	}
	void Scene::Init()
	{
		Entity cameraEntity = GetEntityManager()->Create("MainCamera");
		cameraEntity.AddComponent<Camera>();
		cameraEntity.AddComponent<Transform>();
		cameraEntity.GetComponent<Transform>().SetPosition(Vector3(0, 2, 2));
		//cameraEntity.GetComponent<Transform>().SetRotation(Vector3(glm::radians(180.f), 0.0f, 0.0f));


		cameraEntity.AddComponent<FlyCameraController>();

		

		Vector3 pos = cameraEntity.GetComponent<Transform>().GetPosition();

		// Setup systems here
	}
	void Scene::CleanUp()
	{
		// Destroy all teh gameobjects in teh registry
		DestroyAllGameObjects();

		// Clear other managers if needed

	}
	void Scene::Update(float deltaTime)
	{
		// Update entities transform here

		// get mousePosition HEre;
		Vector2 mousePosition = Input::InputSystem::GetInstance().GetMousePosition();

		/*if (Input::InputSystem::GetInstance().GetKeyDown(Input::Key::G))
		{
			LOG_INFO("Mouse Position : {0}, {1}", mousePosition.x, mousePosition.y);
		}*/

		auto defaultCameraView = m_EntityManager->GetRegistry().view<FlyCameraController>();
		auto cameraView = m_EntityManager->GetRegistry().view<Camera>();
		auto transformView = m_EntityManager->GetRegistry().view<Transform>();


		Camera* camera = nullptr;

		if (!cameraView.empty())
		{
			camera = &cameraView.get<Camera>(cameraView.front());
		}

		if (!defaultCameraView.empty())
		{
			FlyCameraController controller = defaultCameraView.get<FlyCameraController>(defaultCameraView.front());
			Transform* cameraTransform = &transformView.get<Transform>(defaultCameraView.front());


			if (cameraTransform && camera)
			{
				controller.SetCamera(camera);
				Vector3 pos = cameraTransform->GetPosition();

	
				controller.KeyboardInput(*cameraTransform,deltaTime);
				controller.MouseInput(*cameraTransform, mousePosition, deltaTime);

				
			}
		}
		
	}
	const std::string& Scene::GetName() const
	{
		return m_name;
	}
	void Scene::SetName(const std::string& name)
	{
	}

	entt::registry& Scene::GetRegistry()
	{
		return m_EntityManager->GetRegistry();
	}


	Entity Scene::CreateEntity()
	{
		return m_EntityManager->Create();
	}
	Entity Scene::CreateEntity(const std::string& name)
	{
		return m_EntityManager->Create(name);
	}
	Entity Scene::GetEntitybyId(const uint64_t id)
	{
		return m_EntityManager->GetEntitybyId(id);
	}
	EntityManager* Scene::GetEntityManager()
	{
		return m_EntityManager.get();
	}
	void Scene::DestroyAllGameObjects()
	{
		// deletes all teh entities in the registry
		m_EntityManager->Clear();
	}
	void Scene::Serialize(const std::string& filename)
	{
	}
	void Scene::Deserialize(const std::string filename)
	{
	}
}
