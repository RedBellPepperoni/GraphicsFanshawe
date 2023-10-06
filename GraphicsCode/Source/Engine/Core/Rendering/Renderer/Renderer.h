#pragma once
#include "Engine/Core/Rendering/Essentials/Mesh.h"
//#include "Engine/Core/Assets/Camera.h"
#include "ShaderManager.h"
#include <vector>

namespace FanshaweGameEngine
{
	namespace Rendering
	{
		struct RenderElement
		{
			uint32_t shaderId;
			uint32_t VertexOffset;
			uint32_t VertexCount;
			uint32_t IndexOffset;
			uint32_t IndexCount;

			Matrix4 ModelMatrix;
			Matrix3 NormalMatrix;
		};



		class Renderer
		{



		private:

			// Draw Stuff

			void DrawVertices(int vertexCount, size_t vertexOffset);





		public:

			void CalculateRenderElements();
			void DrawFrame();

			void UseShader(const std::string shaderName);
			//Camera GetActiveCamera();

			void Initialize();

		private:


			
			std::vector<RenderElement> renderElementList = {};

			//std::vector<Mesh> loadedMeshArray;

			//GLuint
		public:
			//SharedPtr<ShaderManager> m_shaderManagerHandle = nullptr;


		};
	}
}

