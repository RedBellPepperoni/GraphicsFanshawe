#pragma once
#include "Engine/Core/Rendering/Renderer/Renderer.h"

namespace FanshaweGameEngine
{

	// Forward Delcarartions
	class ShaderLibrary;


	namespace Rendering
	{

		class RenderManager
		{
		private: 
			// The class that actually draws stuff
			Renderer m_renderer;

			// Future case when there can be multiple cameras // 
			// "-1"  means no rendering cameras were found

			int m_mainCameraIndex = -1;


			// The Resource Library that stores all the shaders
			SharedPtr<ShaderLibrary> m_ShaderLibrary;

		//	Camera* m_mainCamera;


		private:

			void LoadEngineShaders();

			void BeginScene();

		public:

			void Init();
			void RenderFrame();


			SharedPtr<ShaderLibrary>& GetShaderLibrary();




		};
	}
}

