#include "RenderManager.h"
#include "Engine/Utils/GLUtils.h"
#include "Engine/Core/Resources/ResourceManager.h"
#include "Engine/Core/Macros/Macro.h"
#include "Engine/Core/Application/Application.h"

#include "Engine/Core/Rendering/Essentials/Camera.h"

#include "Engine/Core/ECS/Components/Transform.h"
#include "Engine/Core/ECS/Components/MeshComponent.h"
#include "Engine/Core/ECS/Components/MeshRenderer.h"

#include "Engine/Core/Rendering/Essentials/Material.h"





namespace FanshaweGameEngine
{
	
	using Components::MeshComponent;
	using Components::MeshRenderer;

	namespace Rendering
	{
		void RenderManager::LoadEngineShaders()
		{
			// Loading the Default Shader 
			// Add other Defaultr Shaders below <----
			//CHECKNULL(GetShaderLibrary()->LoadShader("StandardShader", File::GetShaderDir().string() + "vertexShader01.glsl", File::GetShaderDir().string() + "fragmentShader01.glsl"));
			CHECKNULL(GetShaderLibrary()->LoadShader("StandardShader", File::GetShaderDir().string() + "vert.glsl", File::GetShaderDir().string() + "frag.glsl"));

		}

		void RenderManager::ProcessScene(Scene* scene)
		{

			m_renderer->ClearRenderCache();

			// reference of current scene
			m_currentScene = scene;

			// Temporary copy of registry
			entt::registry& registry = scene->GetRegistry();

			
			// Getting a view of all the cameras in the scene
			auto cameraView = registry.view<Camera>();
			auto transformView = registry.view<Transform>();


			// No rendering cameras found since the view returned empty
			if (cameraView.empty())
			{
				LOG_WARN("No cameras in the scene");
				return;
			}
			


			//// Loop through all the cameras in the scene and send thier data to the pipeline 
			for (entt::entity cameraEntity : cameraView)
			{
				// get the Camera Reference from te view
				Camera& camera = cameraView.get<Camera>(cameraEntity);

				// get the transform of teh camera
				Transform& cameraTransform = transformView.get<Transform>(cameraEntity);

				// Send the data to the Pipeline
				m_renderer->SetUpCameraElement(camera, cameraTransform);
			}


			auto meshView = registry.view<MeshComponent>();
			auto materialView = registry.view<MeshRenderer>();
			
			for (entt::entity meshEntity : meshView)
			{
				MeshComponent& meshComp = meshView.get<MeshComponent>(meshEntity);


				if(!meshComp.isVisible)
				{
					//The mesh is not visible , so dont need to render it
					continue;
				}

				// getting the required components
				MeshRenderer& materialComp = materialView.get<MeshRenderer>(meshEntity);
				Transform transform = transformView.get<Transform>(meshEntity);


				// Getting data from teh Componenets
				SharedPtr<Mesh> renderMesh = meshComp.GetMesh();
				SharedPtr<Material> renderMaterial = materialComp.GetMaterial();

				// Sending the mesh data for processing
				m_renderer->ProcessRenderElement(renderMesh, renderMaterial, transform);


			}

			
			

		}

		


		void RenderManager::Init()
		{
			// Initializing Defaults that will be reused / instanced
			m_renderer = MakeUnique<Renderer>();

			m_renderer->Init();

			// Initializing Shader Library to store all the Loaded Shaders
			m_ShaderLibrary = MakeShared<ShaderLibrary>();


			m_MaterialLibrary = MakeShared<MaterialLibrary>();

			// Loading all the shaders that are default to the engine
			LoadEngineShaders();


			//GLDEBUG(glEnable(GL_DEPTH_TEST));
			//GLDEBUG(glEnable(GL_STENCIL_TEST));
			//GLDEBUG(glEnable(GL_CULL_FACE));
		
			


		}

		void RenderManager::RenderFrame()
		{
			
	
			// Draw the OpaqueEleemnts
			m_renderer->RenderElements(m_ShaderLibrary->GetResource("StandardShader"), MaterialType::Opaque);

		}



		SharedPtr<ShaderLibrary>& RenderManager::GetShaderLibrary()
		{
			return m_ShaderLibrary;
		}
		SharedPtr<MaterialLibrary>& RenderManager::GetMaterialLibrary()
		{
			return m_MaterialLibrary;
		}


		
	}
}