#pragma once
#include "Engine/Core/Memory/Memory.h"
#include <vector>

namespace FanshaweGameEngine
{
	namespace Rendering
	{
		class Material;
    }

	using Rendering::Material;

	namespace Components
	{
		class MeshRenderer
		{
		


		public:

			using MaterialRef = SharedPtr<Material>;
			using MaterialList = std::vector<MaterialRef>;


			

			MeshRenderer();
			MeshRenderer(MaterialRef material);
			MeshRenderer(MaterialList materials);

			~MeshRenderer();

			MaterialRef GetMaterial();
			MaterialList GetMaterials() const;

			//MaterialRef GetMaterial(int index) const;
			
		private:

			MaterialList m_Materials;
			
		};

	}
}


