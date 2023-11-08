#include "Scene.h"
#include "Engine/Core/ECS/Components/ComponentDefinitions.h"
#include "Engine/Core/System/Input/FlyCameraController.h"
// Forward Declarations includes
#include "Engine/Core/ECS/EntityManager.h"
#include "Engine/Core/System/Input/inputSystem.h"
#include "Engine/Core/Rendering/Lights/DirectionLight.h"
#include "Engine/Core/Resources/ResourceManager.h"
#include "Engine/Core/Rendering/Essentials/Camera.h"

#include "Engine/Core/Application/Application.h"



namespace FanshaweGameEngine
{

	Scene::Scene(const std::string& name)
	{
		// Setting up a new Entity Manager with the current scene's Reference
		m_EntityManager = MakeUnique<EntityManager>(this);
		m_directionLight = Factory<DirectionLight>::Create();


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
		Camera* camera = &cameraEntity.AddComponent<Camera>();
		Transform* transform = &cameraEntity.AddComponent<Transform>();

		transform->SetPosition(Vector3(0.0, 0.0f, 0.0));
		transform->SetRotation(Vector3(-90, 0, 0));

		//FlyCameraController* controller = &cameraEntity.AddComponent<FlyCameraController>();
		CameraController* controller = &cameraEntity.AddComponent<CameraController>();
		controller->SetCamera(camera);

		SetMainCamera(controller, transform);


		


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
		
		Vector2 mousePosition = Input::InputSystem::GetInstance().GetMousePosition();

		

		if (mainCameraTransform)
		{
			
			//Vector3 pos = cameraTransform->GetPosition();


			mainCameraController->KeyboardInput(mainCameraTransform, deltaTime);
			mainCameraController->MouseInput(mainCameraTransform, mousePosition, deltaTime);
		}


		Vector3 pos = mainCameraTransform->GetPosition();
		Vector3 rot = mainCameraTransform->GetEulerRotation();

		std::string position = "Position X : " + std::to_string(pos.x) + " Y : " + std::to_string(pos.y) + " Z : " + std::to_string(pos.z) + "Rotation X : " + std::to_string(rot.x) + " Y : " + std::to_string(rot.y) + " Z : " + std::to_string(rot.z);

		Application::GetCurrent().SetWindowTitle(position);
		
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


	void Scene::SetMainCamera(CameraController* controller, Transform* transform)
	{
		mainCameraTransform = transform;
		mainCameraController = controller;

		//LOG_ERROR("Camera Transform : {0} : {1} : {2}", mainCameraTransform->GetPosition().x, mainCameraTransform->GetPosition().y, mainCameraTransform->GetPosition().z);

	}

	void Scene::SetMainCameraPosition(Vector3 position)
	{
		mainCameraTransform->SetPosition(position);
	}






	void Scene::Serialize(const std::string& filename)
	{
	}
	void Scene::Deserialize(const std::string filename)
	{
	}
}
