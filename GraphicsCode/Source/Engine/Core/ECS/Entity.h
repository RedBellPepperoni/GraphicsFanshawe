#pragma once
#include "Engine/Utils/Math.h"
#include "Engine/Core/Scene/Scene.h"
#include "Engine/Core/Memory/Memory.h"
#include "Engine/Utils/UniqueId/UniqueId.h"
#include "Engine/Utils/Logging/Log.h"


// External performant ECS Registry system
#include <entt/entt.hpp>




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

		Scene* m_scene;


	public: 
		
		Entity() = default;

		Entity(entt::entity handle,Scene* scene)
			:m_entityHandle (handle)
			,m_scene(scene)
		{

		}

		~Entity()
		{

		}

		template<typename T, typename... Args>
		T& AddComponent(Args&... args)
		{
#if _DEBUG
			// Check if the component is getting added more tha nonce
#endif

			//m_scene->GetRegistry()

		}

		template<typename T>
		T& GetComponent()
		{
			// Return component here
		}

		template<typename T>
		T* TryGetComponent()
		{
			//return the compoentn
		}


		template <typename T>
		bool HasComponent()
		{
			return false;
		}


		template<typename T>
		void RemoveComponent()
		{

		}

		template<typename T>
		void TryRemoveComponent()
		{

		}

		bool IsActive()
		{

		}

		void SetActive(bool isActive)
		{

		}

		//Transform&

		uint64_t GetId()
		{

		}

		const std::string& GetName()
		{

		}

		void Setparent(Entity entity)
		{

		}

		Entity GetParent()
		{

		}

		std::vector<Entity> GetChildren()
		{

		}

		void ClearChildren()
		{

		}

		entt::entity GetHandle()
		{
			return m_entityHandle;
		}

		void Destroy()
		{

		}

		bool IsValid()
		{

		}

		SharedPtr<Scene> GetSceen() const
		{

		}



	};
}

