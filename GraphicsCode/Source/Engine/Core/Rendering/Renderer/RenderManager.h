#pragma once
#include "Engine/Core/Rendering/Renderer/Renderer.h"

namespace FanshaweGameEngine
{

	// Forward Delcarartions
	class ShaderLibrary;
	class MaterialLibrary;
	



	namespace Rendering
	{

		
		
	
		class RenderManager
		{
		private: 
			// The class that actually draws stuff
			UniquePtr<Renderer> m_renderer;

			// The Resource Library that stores all the shaders
			SharedPtr<ShaderLibrary> m_ShaderLibrary;

			SharedPtr<MaterialLibrary> m_MaterialLibrary;

		//	Camera* m_mainCamera;


		private:

			void LoadEngineShaders();

			void BeginScene();

			

		public:

			void Init();

			void RenderFrame();


			SharedPtr<ShaderLibrary>& GetShaderLibrary();


			SharedPtr<MaterialLibrary>& GetMaterialLibrary();

		};
	}
}

