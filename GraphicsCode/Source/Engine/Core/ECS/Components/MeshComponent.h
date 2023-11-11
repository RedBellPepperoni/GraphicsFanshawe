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


			//MeshComponent();
			explicit MeshComponent(const SharedPtr<Mesh>& meshRef);


			const SharedPtr<Mesh>& GetMesh();
			void SetMesh(SharedPtr<Mesh> mesh);
				
			SharedPtr<Mesh> m_handle;
			bool isVisible = true;
			bool castsShadow = true;

		};


	}
}

