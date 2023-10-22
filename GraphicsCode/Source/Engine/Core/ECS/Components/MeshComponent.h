#pragma once
#include "Engine/Core/Memory/Memory.h"

namespace FanshaweGameEngine
{
	//Forward Declaration
	namespace Rendering 
	{
		class Mesh;
	}

	using Rendering::Mesh;

	namespace Components
	{

		struct MeshComponent
		{


			MeshComponent();
			MeshComponent(const SharedPtr<Mesh>& meshRef);


			const SharedPtr<Mesh>& GetMesh();
				
			SharedPtr<Mesh> meshHandle;
			bool isVisible = true;
			bool castsShadow = true;

		};


	}
}

