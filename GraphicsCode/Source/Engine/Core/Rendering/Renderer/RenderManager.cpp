#include "RenderManager.h"

// Include teh scene before Application
#include "Engine/Core/Scene/Scene.h"
#include "Engine/Core/ECS/EntityManager.h"


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

			CHECKNULL(GetShaderLibrary()->LoadShader("StandardShader", File::GetShaderDir().string() + "textureVert.glsl", File::GetShaderDir().string() + "textureFrag.glsl"));
			//CHECKNULL(GetShaderLibrary()->LoadShader("StandardShader", File::GetShaderDir().string() + "vert.glsl", File::GetShaderDir().string() + "frag.glsl"));

		}

		void RenderManager::ProcessScene(Scene* scene)
		{
			// Clear the Data of the Pipeline
			m_renderer->ClearRenderCache();

			// get all the Entities that have the "Camera" Component
			ComponentView cameraView = scene->GetEntityManager()->GetComponentsOfType<Camera>();


			// No rendering cameras found since the view returned empty
			if (cameraView.IsEmpty())
			{
				LOG_WARN("No cameras in the scene");
				return;
			}
			
			//// Loop through all the cameras in the scene and send therr data to the pipeline 
			for (Entity cameraObject : cameraView)
			{
				Camera& camera = cameraObject.GetComponent<Camera>();
				Transform& transform = cameraObject.GetComponent<Transform>();

				m_renderer->SetUpCameraElement(camera, transform);
			}



			// Getting a view of all the Objects which have a "mesh" componenet
			ComponentView meshView = scene->GetEntityManager()->GetComponentsOfType<MeshComponent>();
			
			// Looping through all the entities that have a mesh component

			for (Entity meshObject : meshView)
			{

				MeshComponent& meshComp = meshObject.GetComponent<MeshComponent>();

				if(!meshComp.isVisible)
				{
					//The mesh is not visible , so dont need to render it
					continue;
				}

				// getting the required components
				MeshRenderer& materialComp = meshObject.GetComponent<MeshRenderer>();
				Transform& transform = meshObject.GetComponent<Transform>();


				// Sending the mesh data for processing
				m_renderer->ProcessRenderElement(meshComp.GetMesh(), materialComp.GetMaterial(), transform);

			}

					

		}

		


		void RenderManager::Init()
		{
			

			// Initializing Shader Library to store all the Loaded Shaders
			m_ShaderLibrary = MakeShared<ShaderLibrary>();

			m_MaterialLibrary = MakeShared<MaterialLibrary>();

			// Loading all the shaders that are default to the engine
			LoadEngineShaders();


			GLDEBUG(glEnable(GL_DEPTH_TEST));
			GLDEBUG(glEnable(GL_STENCIL_TEST));
			GLDEBUG(glEnable(GL_CULL_FACE));
			GLDEBUG(glCullFace(GL_BACK));

			// Initializing Defaults that will be reused / instanced
			m_renderer = MakeUnique<Renderer>();

			m_renderer->Init();
		
			


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