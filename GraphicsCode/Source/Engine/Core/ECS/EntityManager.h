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
		class iterator;
		using ComponentView = entt::view<entt::get_t<Component...>>;

	public:

		Scene* m_scene = nullptr;
		ComponentView m_view;

		EntityView(Scene* scene)
			: m_scene(scene)
			, m_view(scene->GetRegistry().view<Component...>())
		{

		}

		Entity operator[](int i) 
		{		
			// Out of bounds : This should realistically not happen
			if (i >= Size())
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

		iterator begin()
		{
			return EntityView<Component...>::iterator(*this, 0);
		}

		iterator end()
		{
			return EntityView<Component...>::iterator(*this, Size());
		}

		// Custom class for iterating through our
		class iterator
		{
		public:

			using pointer = Entity*;
			using reference = Entity&;

			explicit iterator(EntityView<Component...>& view, size_t index = 0)
				: m_View(view)
				, m_Index(index)
			{
			}

			Entity operator*() const
			{
				return m_View[int(m_Index)];
			}

			iterator& operator++()
			{
				m_Index++;
				return *this;
			}

			iterator operator++(int)
			{
				iterator temp = *this;
				++(*this);
				return temp;
			}

			bool operator!=(const iterator& rhs) const
			{
				return m_Index != rhs.m_Index;
			}
		private:
			size_t m_Index = 0;
			EntityView<Component...>& m_View;
		};
		

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
		EntityView<Component...> GetComponentsOfType()
		{
			return EntityView<Component...>(m_scene);
		}
		

		// Sunction to make sure that when creating an element the dependants are avaibale
		template <typename R, typename T>
		void AddDependency()
		{
			m_registry.template on_construct<R>().template connect<&entt::registry::get_or_emplace<T>>();
		}
		

		entt::registry& GetRegistry();
		
		Entity GetEntitybyId(uint64_t id);
		

	
	};

	
}

