#include "MeshComponent.h"
#include "Engine/Core/Resources/ResourceManager.h"
#include "Engine/Core/Rendering/Essentials/Mesh.h"


namespace FanshaweGameEngine
{

	namespace Components
	{
		MeshComponent::MeshComponent()
			:meshHandle(Factory<Mesh>::Create())
		{

		}
		MeshComponent::MeshComponent(const SharedPtr<Mesh>& meshRef)
			:meshHandle(meshRef)
		{
		}

		const SharedPtr<Mesh>& MeshComponent::GetMesh()
		{
			return meshHandle;
		}
	}

}
