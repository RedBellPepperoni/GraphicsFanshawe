#include "MeshComponent.h"
#include "Engine/Core/Resources/ResourceManager.h"
#include "Engine/Core/Rendering/Essentials/Mesh.h"


namespace FanshaweGameEngine
{

	namespace Components
	{
		/*MeshComponent::MeshComponent()
			:m_handle(Factory<Mesh>::Create())
		{

		}*/

		MeshComponent::MeshComponent(const SharedPtr<Mesh>& meshRef)
			: m_handle(meshRef)
			
		{

		}
	

		const SharedPtr<Mesh>& MeshComponent::GetMesh()
		{
			return m_handle;
		}


		void MeshComponent::SetMesh(SharedPtr<Mesh> mesh)
		{

			m_handle = mesh;
		}
	}

}
