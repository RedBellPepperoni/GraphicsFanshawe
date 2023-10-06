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
	}

	using Rendering::Mesh;



	
	/// Temporary class to handle 

	class GameObject
	{
	

	public:

		GameObject() = default;
		GameObject(const SharedPtr<Mesh>& mesh);
		GameObject(const Transform& transform, const SharedPtr<Mesh>& mesh);
		~GameObject();


	public:
		
		// All objects should have a transform
		Transform m_transform;

		// For now hardcoding mesh in the gameObject
		// TODO: Change this to a seperate component later !!
		SharedPtr<Mesh> m_rendermesh;
		uint32_t m_shaderID;
		
		void AttachShader(const uint32_t& shaderID);

	};

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

