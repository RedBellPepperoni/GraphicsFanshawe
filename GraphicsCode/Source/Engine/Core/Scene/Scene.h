#pragma once
#include "Engine/Core/Memory/Memory.h"
#include <string>
#include "Engine/Utils/Math.h"

// The Entt Library header
#include <entt/entity/registry.hpp>


namespace FanshaweGameEngine 
{

	class EntityManager;
	class Entity;
	class CameraController;	
	class DirectionLight;

	namespace Components
	{
		class Transform;
	}

	using Components::Transform;


	class Scene
	{

	private:

		// Name of the Scene
		std::string m_name;
		
		// The Refernce to the Entity Manager wrapper class 
		UniquePtr<EntityManager> m_EntityManager = nullptr;

		SharedPtr<DirectionLight> m_directionLight = nullptr;

		Transform* mainCameraTransform = nullptr;
		CameraController* mainCameraController = nullptr;


	public:

		// Should make this explicit later on to avoid unnamed scenes
		Scene(const std::string& name);

		// Destructor
		~Scene();

		// The initialzation of the scen and registries
		void Init();

		// the deletion of the scene and registries
		void CleanUp();

		// this should be called everyframe to update teh trasnforms and such
		void Update(float deltaTime);

		// getter for accessing the scene name
		const std::string& GetName() const;

		// Setter to change the scene name
		void SetName(const std::string& name);

		// Wrapper around the entt registry
		entt::registry& GetRegistry();

		// Creates and returns a new entity
		Entity CreateEntity();

		// Create a new entity with the provided name and return it
		Entity CreateEntity(const std::string& name);

		// Find a entity by the given ID if it exists
		Entity GetEntitybyId(const uint64_t id);

		// The publically accessible Pointer to the Entity manager
		EntityManager* GetEntityManager();

		// Loops through all the Entitys in the scene and destroys them
		void DestroyAllGameObjects();

		void SetMainCamera(CameraController* controller, Transform* transform);
		
		void SetMainCameraPosition(const Vector3 position);

		void Serialize(const std::string& filename);
		void Deserialize(const std::string filename);

		Transform* GetMainCameraTransform() const;

	};

}

