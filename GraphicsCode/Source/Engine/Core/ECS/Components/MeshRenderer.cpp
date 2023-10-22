#include "MeshRenderer.h"
#include "Engine/Utils/Logging/Log.h"
#include "Engine/Core/Resources/ResourceManager.h"
#include "Engine/Core/Rendering/Essentials/Material.h"

namespace FanshaweGameEngine
{
	namespace Components
	{
		MeshRenderer::MeshRenderer()
			:m_Materials(1, Factory<Material>::Create())
		{
		}
		MeshRenderer::MeshRenderer(MaterialRef material)
			: m_Materials(1, material)
		{
		}
		MeshRenderer::MeshRenderer(MaterialList materials)
			: m_Materials(materials)
		{
		}
		MeshRenderer::~MeshRenderer()
		{
		}

		MeshRenderer::MaterialRef MeshRenderer::GetMaterial() const
		{
			if (m_Materials.empty())
			{
				LOG_ERROR("No Materials Found");
				return nullptr;
			}

			return m_Materials[0];
			
		}

		MeshRenderer::MaterialList MeshRenderer::GetMaterials() const
		{
			return m_Materials;
		}


		MeshRenderer::MaterialRef MeshRenderer::GetMaterial(int index) const
		{
			if (m_Materials.empty())
			{
				LOG_ERROR("No Materials Found");
				return nullptr;
			}

			if (m_Materials.size() < index)
			{
				LOG_ERROR("Out of Bounds material index specifed");
				return nullptr;
			}

			return m_Materials[index];
		}
	}
}