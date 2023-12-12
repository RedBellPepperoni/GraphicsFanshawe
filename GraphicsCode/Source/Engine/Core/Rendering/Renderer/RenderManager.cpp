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
#include "Engine/Core/Rendering/Lights/Light.h"
#include "Engine/Core/Rendering/Essentials/Cubemap.h"


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

			CHECKNULL(GetShaderLibrary()->LoadShader("StandardShader", File::GetShaderDir().string() + "forwardVert.glsl", File::GetShaderDir().string() + "forwardFrag.glsl"));
			CHECKNULL(GetShaderLibrary()->LoadShader("SkyboxShader", File::GetShaderDir().string() + "skyboxVert.glsl", File::GetShaderDir().string() + "skyboxFrag.glsl"));
			CHECKNULL(GetShaderLibrary()->LoadShader("DebugLineShader", File::GetShaderDir().string() + "DebugLineVert.glsl", File::GetShaderDir().string() + "DebugLineFrag.glsl"));
			CHECKNULL(GetShaderLibrary()->LoadShader("DebugPointShader", File::GetShaderDir().string() + "DebugPointVert.glsl", File::GetShaderDir().string() + "DebugPointFrag.glsl"));
			CHECKNULL(GetShaderLibrary()->LoadShader("TransparentShader", File::GetShaderDir().string() + "transparentVert.glsl", File::GetShaderDir().string() + "transparentFrag.glsl"));
			
			
			
			//CHECKNULL(GetShaderLibrary()->LoadShader("StandardShader", File::GetShaderDir().string() + "textureVert.glsl", File::GetShaderDir().string() + "textureFrag.glsl"));
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

			ComponentView lightView = scene->GetEntityManager()->GetComponentsOfType<Light>();

			for (Entity lightObject : lightView)
			{
				Light& lightComponent = lightObject.GetComponent<Light>();
				Transform* transform = &lightObject.GetComponent<Transform>();
				m_renderer->ProcessLightElement(lightComponent, *transform);



				
			}

					

		}

		


		void RenderManager::Init()
		{
			

			// Initializing Shader Library to store all the Loaded Shaders
			m_ShaderLibrary = MakeShared<ShaderLibrary>();

			m_MaterialLibrary = MakeShared<MaterialLibrary>();

			// Loading all the shaders that are default to the engine
			LoadEngineShaders();


			
			GLDEBUG(glEnable(GL_STENCIL_TEST));
			// While drawing a pixel, see if the pixel that's already there is closer or not?
			GLDEBUG(glEnable(GL_DEPTH_TEST));

			//Enabling Transparency
			GLDEBUG(glEnable(GL_BLEND));
			GLDEBUG(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
			//GLDEBUG(glEnable(GL_CULL_FACE));
			//GLDEBUG(glCullFace(GL_BACK));

			// Initializing Defaults that will be reused / instanced
			m_renderer = MakeUnique<Renderer>();

			m_renderer->Init();

			SharedPtr<Shader> lineShader = m_ShaderLibrary->GetResource("DebugLineShader");
			SharedPtr<Shader> pointShader = m_ShaderLibrary->GetResource("DebugPointShader");

			m_renderer->SetupDebugShaders(lineShader, pointShader);

			//m_renderer->SetSkyboxCubeMap(m_Texture->GetResource("DefaultSkyBox");
		
			


		}

		void RenderManager::RenderFrame()
		{

			int cameraIndex = Application::GetCurrent().GetMainCameraIndex();

			if (cameraIndex < 0)
			{
				LOG_WARN("No Rendering Cameras");
				return;
			}
	
			// Store the data for the current rendering camera
			const CameraElement& cameraElement = m_renderer->GetPipeLine().cameraList[cameraIndex];

			// ===== Post Render Skybox Pass =================
			m_renderer->SkyBoxPass(m_ShaderLibrary->GetResource("SkyboxShader"), cameraElement);
	

			// ===== Forward Pass for Opaque Elements ================ 
		    m_renderer->ForwardPass(m_ShaderLibrary->GetResource("StandardShader"), cameraElement , MaterialType::Opaque);


			m_renderer->ForwardPass(m_ShaderLibrary->GetResource("TransparentShader"), cameraElement , MaterialType::Transparent);


			m_renderer->DebugPass(cameraElement);

			

			

		}

		UniquePtr<Renderer>& RenderManager::GetRenderer()
		{
			return m_renderer;
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