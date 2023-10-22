#pragma once
#include "Engine/Core/Memory/Memory.h"
#include "Engine/Core/ECS/Components/Transform.h"
#include <unordered_map>
#include <string>

namespace FanshaweGameEngine
{
	namespace Rendering
	{
		class Mesh;
		class Material;
	}

	using Rendering::Mesh;
	using Rendering::Material;


	
	/// Temporary class to handle gameobjects, switching to an ECS system later

	class GameObject
	{
	

	public:

		GameObject() = default;
		GameObject(const SharedPtr<Mesh>& mesh);
		//GameObject(const Transform& transform, const SharedPtr<Mesh>& mesh);
		~GameObject();


	public:
		
		// All objects should have a transform
		//Transform m_transform;

		// For now hardcoding mesh in the gameObject
		// TODO: Change this to a seperate component later !!
		SharedPtr<Mesh> m_rendermesh;

		// The material Data
		SharedPtr<Material> m_material;


		bool shouldDraw = true;
		
		

	};


	// Psuedo ECS registry, need to do memory pooling for faster access

	class GameObjectRegistry
	{

		using ObjectRegistry = std::unordered_map<std::string, SharedPtr<GameObject>>;

	public: 


		GameObjectRegistry();
		~GameObjectRegistry();

		 SharedPtr<GameObject> CreateObject(const SharedPtr<Mesh>& mesh, const std::string& friendlyName);

		 ObjectRegistry Get();
		

	private:

		ObjectRegistry m_objectRegistry = {};

		


	};
}

