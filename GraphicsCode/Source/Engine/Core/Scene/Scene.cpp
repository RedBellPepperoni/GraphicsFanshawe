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
		
	}
	void Scene::Init()
	{
	}
	void Scene::CleanUp()
	{
	}
	void Scene::Update()
	{
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
		return Entity();
	}
	Entity Scene::CreateEntity(const std::string& name)
	{
		return Entity();
	}
	Entity Scene::GetEntitybyId(const uint64_t id)
	{
		return Entity();
	}
	EntityManager* Scene::GetEntityManager()
	{
		return nullptr;
	}
	void Scene::DestroyAllGameObjects()
	{
	}
}
