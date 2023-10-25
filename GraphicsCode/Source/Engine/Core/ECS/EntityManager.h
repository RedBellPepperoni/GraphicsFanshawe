#pragma once
#include "Entity.h"
#include <string>


namespace FanshaweGameEngine
{
	// Forward Declaration
	class Scene;
	
	template <typename... Component>
	struct EntityView
	{
		using TypeView = entt::view<entt::get_t<Component...>>;

	public:

		SharedPtr<Scene> m_scene = nullptr;
		TypeView m_view;

		EntityView(SharedPtr<Scene> scene)
			: m_scene(scene)
			,m_view(scene->GetRegistry.view<Component...>())
		{

		}

		Entity operator[](int i) 
		{		
			if (i < Size())
			{
				LOG_ERROR("Index out of bound on EntityView");
				__debugbreak();
			}

			return Entity(m_view[i], m_scene);
		}

		bool IsEmpty() const 
		{ 
			return m_view.empty(); 
		}

		size_t Size() const 
		{
			return m_view.size();
		}


	};
	
	

	class EntityManager
	{
	private: 

		Scene* m_scene = nullptr;
		entt::registry m_registry;

	public:

		EntityManager(Scene* scene)
			: m_scene(scene)
		{
			m_registry = {};
		}

		Entity Create();

		Entity Create(const std::string& name);
		

		void Clear();
	

		template<typename... Component>
		EntityView<Component...> GetEntitiesOfType();
		

		// Sunction to make sure that when creating an element the dependants are avaibale
		template <typename R, typename T>
		void AddDependency();
		

		entt::registry& GetRegistry();
		
		Entity GetEntitybyId(uint64_t id);
		

	
	};

	
}

