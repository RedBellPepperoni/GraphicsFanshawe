#include "RenderManager.h"
#include "Engine/Utils/GLUtils.h"
#include "Engine/Core/Resources/ResourceManager.h"
#include "Engine/Core/Macros/Macro.h"
#include "Engine/Core/Application/Application.h"
#include "Engine/Core/ECS/Object/GameObject.h"
#include "Engine/Core/Rendering/Essentials/Material.h"





namespace FanshaweGameEngine
{
	

	namespace Rendering
	{
		void RenderManager::LoadEngineShaders()
		{
			// Loading the Default Shader 
			// Add other Defaultr Shaders below <----
			//CHECKNULL(GetShaderLibrary()->LoadShader("StandardShader", File::GetShaderDir().string() + "vertexShader01.glsl", File::GetShaderDir().string() + "fragmentShader01.glsl"));
			CHECKNULL(GetShaderLibrary()->LoadShader("StandardShader", File::GetShaderDir().string() + "vert.glsl", File::GetShaderDir().string() + "frag.glsl"));

		}

		void RenderManager::BeginScene()
		{
			// Load All object in the scene 

	

			SharedPtr<GameObjectRegistry> objRegistry = Application::GetCurrent().GetObjectLibrary();

			// Loop through all the Gameobjects in the current scene 
			for (auto& itr : objRegistry->Get())
			{
				Transform objTransform = itr.second->m_transform; 
				SharedPtr<Mesh> objMesh = itr.second->m_rendermesh;
				SharedPtr<Material> objMat = itr.second->m_material;
				std::string debugName = itr.first;

				if(!itr.second->shouldDraw) 
				{
					// The Object shouldn't be submitted for rendering
					continue;
				}

				// Push the Data to the Render Element Queue.

				m_renderer->ProcessRenderElement(objMesh,objMat,objTransform,debugName);


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
			// We gather all the Objects in the Scene and Push the mto the Render Queue
			BeginScene();

			
			// Get al the rendering cameras in teh scene
			std::vector<SharedPtr<Camera>> allRenderingCameras = Application::GetCurrent().GetSceneCameras();

			// Send the camera data to the pipeline
			for (size_t index = 0; index < allRenderingCameras.size(); index++)
			{
				m_renderer->SetUpCameraElement(allRenderingCameras[index]);
			}
			

		
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