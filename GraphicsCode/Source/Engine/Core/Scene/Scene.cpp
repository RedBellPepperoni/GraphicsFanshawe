#include "Scene.h"
#include "Engine/Core/ECS/Components/ComponentDefinitions.h"
#include "Engine/Core/System/Input/FlyCameraController.h"
// Forward Declarations includes
#include "Engine/Core/ECS/EntityManager.h"
#include "Engine/Core/System/Input/inputSystem.h"
#include "Engine/Core/Rendering/Lights/Light.h"
#include "Engine/Core/Resources/ResourceManager.h"
#include "Engine/Core/Rendering/Essentials/Camera.h"
#include "Engine/Core/Application/Application.h"
#include "DefaultCameraController.h"
#include "Engine/Core/LuaIntegration/LuaManager.h"
#include "Engine/Core/ECS/Components/LuaScriptComponent.h"
#include "Engine/Core/Audio/AudioListener.h"

#include <sol/sol.hpp>


namespace FanshaweGameEngine
{


	Scene::Scene(const std::string& name)
	{
		// Setting up a new Entity Manager with the current scene's Reference
		m_EntityManager = MakeUnique<EntityManager>(this);
		//m_directionLight = Factory<DirectionLight>::Create();

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

		//AudioListener* listener = &cameraEntity.AddComponent<Audio::AudioListener>(transform);


		transform->SetPosition(Vector3(8.0f, 3.5f, 4.0f));
		transform->SetEularRotation(Vector3(-15.0f, 57.0f, 0.0f));

		cameraEntity.AddComponent<DefaultCameraController>(DefaultCameraController::CameraType::FlyCam);
		

		LuaManager::GetInstance().OnInit(this);
		

		// Setup systems here
	}
	void Scene::CleanUp()
	{


		// Destroy all teh gameobjects in teh registry
		DestroyAllGameObjects();

		//LuaManager::GetInstance().GetState().collect_garbage();

		// Clear other managers if needed

	}


	void Scene::Update(float deltaTime)
	{
		
		Vector2 mousePosition = Input::InputSystem::GetInstance().GetMousePosition();

		
		ComponentView cameraControllerView = m_EntityManager->GetComponentsOfType<DefaultCameraController>();

		ComponentView cameraview = m_EntityManager->GetComponentsOfType<Camera>();
		ComponentView audioListenerView = m_EntityManager->GetComponentsOfType<AudioListener>();


		Camera* camera = nullptr;

		if (!cameraview.IsEmpty())
		{
			camera = &cameraview[0].GetComponent<Camera>();
		}




		if (!cameraControllerView.IsEmpty())
		{
			DefaultCameraController& controller = cameraControllerView[0].GetComponent<DefaultCameraController>();
			Transform* transform = cameraControllerView[0].TryGetComponent<Transform>();

			if (transform && controller.GetController())
			{

				controller.GetController()->SetCamera(camera);
				controller.GetController()->KeyboardInput(*transform, deltaTime);
				controller.GetController()->MouseInput(*transform, mousePosition, deltaTime);

				Vector3 pos = transform->GetPosition();
				Vector3 rot = transform->GetEulerRotation();

				string fps = std::to_string(Application::GetCurrent().GetFPS());

				std::string position = "Position X : " + std::to_string(pos.x) + " Y : " + std::to_string(pos.y) + " Z : " + std::to_string(pos.z) + "Rotation X : " + std::to_string(rot.x) + " Y : " + std::to_string(rot.y) + " Z : " + std::to_string(rot.z);

				Application::GetCurrent().SetWindowTitle(position);

			}



		}
		

		/*if (!audioListenerView.IsEmpty())
		{
			if (audioListenerView.Size() > 1)
			{
				LOG_WARN("More than One Audio Listeners in the scene");
			}

			AudioListener* listener = &audioListenerView[0].GetComponent<AudioListener>();

			listener->Update(deltaTime);
		}*/
		

		
		
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


	void Scene::SetMainCamera(CameraController* controller, Transform* transform, AudioListener* listener)
	{
		mainCameraTransform = transform;
		mainCameraController = controller;
		mainAudioListener = listener;
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

	Transform* Scene::GetMainCameraTransform() const
	{
		return mainCameraTransform;
	}
}
