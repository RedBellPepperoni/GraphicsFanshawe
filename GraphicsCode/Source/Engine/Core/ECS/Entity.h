#pragma once
#include "Engine/Utils/Math.h"
#include "Engine/Core/Scene/Scene.h"
#include "Engine/Core/Memory/Memory.h"
#include "Engine/Utils/UniqueId/UniqueId.h"
#include "Engine/Utils/Logging/Log.h"

__pragma(warning(push))
// External performant ECS Registry system
#include <entt/entt.hpp>
__pragma(warning(pop))



namespace FanshaweGameEngine
{

	struct IdComponent
	{
		// The Unique Identifier
		UniqueId ID;

		//Can Add saving and loading here

	};

	struct NameComponent
	{
		// The name of the Entity
		std::string name = "";
	};


	// Header Only Entity class wrapping arounf the entt system
	class Entity
	{
	private:

		entt::entity m_entityHandle = entt::null;

		bool m_isActive = true;

		Scene* m_scene;


	public: 
		
		Entity() = default;

		Entity(entt::entity handle, Scene* scene)
			:m_entityHandle (handle)
			,m_scene(scene)
		{

		}

		~Entity()
		{

		}

		bool IsActive()
		{
			return m_isActive;
		}

		void SetActive(const bool active)
		{
			m_isActive = active;
		}


		template<typename T, typename... Args>

		T& AddComponent(Args&... args)
		{
			if (HasComponent<T>())
			{
				LOG_WARN("Trying to add the component more than once");
			}

			return m_scene->GetRegistry().emplace <T>(m_entityHandle, std::forward<Args>(args)...);

		}

		template<typename T>
		T& GetComponent()
		{
			// Return component here
			return m_scene->GetRegistry().get<T>(m_entityHandle);
		}

		template<typename T>
		T* TryGetComponent()
		{
			return m_scene->GetRegistry().try_get<T>(m_entityHandle);
		}


		template <typename T>
		bool HasComponent()
		{
			
			return m_scene->GetRegistry().all_of<T>(m_entityHandle);
		}


		template<typename T>
		void RemoveComponent()
		{
			m_scene->GetRegistry().remove<T>(m_entityHandle);
		}

		template<typename T>
		void TryRemoveComponent()
		{
			if (HasComponent<T>())
			{
				RemoveComponent<T>();
			}
		}

		


		//Transform&

		uint64_t GetId()
		{
			return m_scene->GetRegistry().get<IdComponent>(m_entityHandle).ID.GetId();
		}

		const std::string& GetName()
		{

			NameComponent* comp = TryGetComponent<NameComponent>();

			if(comp)
			{
				return comp->name;
			}
			else
			{		
				return "unamedEntity";
			}

		}

		void SetParent(Entity entity)
		{
			// Add parents here
		}

		Entity GetParent()
		{
			// get entity ref of parent
		}

		std::vector<Entity> GetChildren()
		{
			//Get entity ref of children
		}

		void ClearChildren()
		{
			//null all the refs of children
		}

		entt::entity GetHandle()
		{
			return m_entityHandle;
		}

		void Destroy()
		{
			m_scene->GetRegistry().destroy(m_entityHandle);
		}

		bool IsValid()
		{
			return m_scene->GetRegistry().valid(m_entityHandle) && m_scene;
		}

		Scene* GetScene() const
		{
			return m_scene;
		}



	};
}

