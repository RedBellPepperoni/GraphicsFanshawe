#pragma once
#include "File.h"
#include "Engine/Core/Rendering/Essentials/Mesh.h"
#include "Engine/Utils/Loading/ModelLoader.h"

namespace FanshaweGameEngine
{
	// Class to store multiple sub meshes and their specified data 
	
	class Model
	{

	private:
		std::vector<SharedPtr<Mesh>> m_meshes;
		//std::vector<Transform> m_MeshTransform;

		FilePath fileLocation;

	public:

		Model() = default;
		Model(const FilePath& filepath);

		std::vector<SharedPtr<Mesh>>& GetMeshes();
		
		void Load(const FilePath& filepath);

	};
}

