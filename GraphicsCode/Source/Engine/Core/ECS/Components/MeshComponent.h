#pragma once
#include "Engine/Core/Memory/Memory.h"
#include <string>

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
				
			SharedPtr<Mesh> m_handle;
			bool isVisible = true;
			bool castsShadow = true;

		};


	}
}

