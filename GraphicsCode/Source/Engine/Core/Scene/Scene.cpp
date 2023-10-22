#include "Scene.h"

// Forward Declarations includes
#include "Engine/Core/ECS/EntityManager.h"


namespace FanshaweGameEngine
{
	Scene::Scene(const std::string& name)
	{
		// Setting up a new Entity Manager with the current scene's Reference
		m_EntityManager = MakeUnique<EntityManager>(this);
	}
	Scene::~Scene()
	{
		// Cleanup the manager
		m_EntityManager->Clear();
	}
	void Scene::Init()
	{
		// Setup systems here
	}
	void Scene::CleanUp()
	{
		// Destroy all teh gameobjects in teh registry
		DestroyAllGameObjects();

		// Clear other managers if needed

	}
	void Scene::Update()
	{
		// Update entities transform here
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
