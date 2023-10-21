#pragma once
#include "Engine/Core/Memory/Memory.h"
#include <string>

// The Entt Library header
#include <entt/entity/registry.hpp>


namespace FanshaweGameEngine 
{

	class EntityManager;
	class Entity;

	class Scene
	{

	private:

		std::string m_name;
		
		UniquePtr<EntityManager> m_EntityManager;



	public:

		// Should make this explicit later on to avoid unnamed scenes
		Scene(const std::string& name);
		~Scene();


		void Init();
		void CleanUp();

		void Update();


		const std::string& GetName() const;

		void SetName(const std::string& name);

		entt::registry& GetRegistry();

		Entity CreateEntity();
		Entity CreateEntity(const std::string& name);

		Entity GetEntitybyId(const uint64_t id);

		EntityManager* GetEntityManager();


		void DestroyAllGameObjects();


	};

}

