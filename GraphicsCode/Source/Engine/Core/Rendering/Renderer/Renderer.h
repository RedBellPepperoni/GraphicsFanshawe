#pragma once
#include "Engine/Utils/Math.h"
#include "Engine/Core/Memory/Memory.h"


//#include "Engine/Core/Assets/Camera.h"
#include <string>
#include <vector>

namespace FanshaweGameEngine
{
	namespace Components
	{
		// Forward Decalrartions for better compile times
		class Transform;
	}
	
	
	using Components::Transform;
	
	
	struct Light;
	enum class LightType : uint8_t;

	namespace Rendering
	{
		// Forward Decalrartions for better compile times
		class Mesh;
		class Material;
		class VertexArray;
		class Shader;
		class Camera;
		class Texture;
		

		enum class MaterialType;


		// Data Structure to define Renderable Object properties
		struct RenderElement
		{
			// Stores the material of the current Eleemnt
			size_t materialIndex;

			// Defines which mesh is used for teh current Unit
			size_t meshIndex;

			// Define the transform/ model matrix
			Matrix4 ModelMatrix;

			// Defines the Normal matrix : used for calculating lights			
			Matrix4 NormalMatrix;
		};

		struct LightElement
		{
			std::string uniformName;
			Vector3 color;
			Vector3 position;
			Vector3 direction;

			float intensity;
			float radius;
			LightType type;
			float innerAngle;
			float outerAngle;
		};


		// Data Structure to define main camera properties
		struct CameraElement
		{
		
			Matrix4 viewProjMatrix;
			//Matrix4 viewMatrix;
			Vector3 viewPosition;

			float aspectRatio;
			bool isOrtho;
		};


		struct PipeLine
		{
			

			// The Verte array for the current Pipeline
			SharedPtr<VertexArray> VAO;

			// All the Render Elements that need to be drawn
			std::vector<RenderElement> renderElementList;

			std::vector<LightElement> lightElementList;
		
			// All the Material for the current loaded Render Elements
			std::vector<SharedPtr<Material>> MaterialList;

			// All the mehses that needs to be drawn
			std::vector<SharedPtr<Mesh>> MeshList;


			// The indices of all the Opaque Shader Elements
			std::vector<size_t> opaqueElementList;

			// properties of all the Cameras that are in the scene
			std::vector<CameraElement> cameraList;


			int textureBindIndex = 0;

			SharedPtr<Texture> defaultTextureMap;
			
		};



		class Renderer
		{
			


		
		private:
			

			
			
			PipeLine m_pipeline;

			void DrawVertices(uint32_t vertexCount, size_t vertexOffset);	

			void DrawIndices(uint32_t indexCount, uint32_t indexOffset = 0);
			
			void DrawElement(const CameraElement& camera, SharedPtr<Shader>& shader, const RenderElement& element);

			
			void SetLightUniform(SharedPtr<Shader>& shader);
			
			
		public:

			void Init();

			const PipeLine GetPipeLine() const;

			// Draws the provided Elements with the provided shader
			void RenderElements( SharedPtr<Shader> shader, const MaterialType type);

			void SetUpCameraElement(Camera& cameraRef, Transform& transform);

			// Adds a Render Element to the Queue
			void ProcessRenderElement(const SharedPtr<Mesh>& mesh, const SharedPtr<Material>& material, Transform& transform);
			void ProcessLightElement(Light& light, Transform& transform);

			
			void ClearRenderCache();
			

			
		};
	}
}

