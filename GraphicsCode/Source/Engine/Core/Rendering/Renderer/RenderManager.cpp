#include "RenderManager.h"
#include "Engine/Utils/GLUtils.h"
#include "Engine/Core/Resources/ResourceManager.h"
#include "Engine/Core/Macros/Macro.h"
#include "Engine/Core/Application/Application.h"
#include "Engine/Core/ECS/Object/GameObject.h"



namespace FanshaweGameEngine
{
	



	namespace Rendering
	{
		void RenderManager::LoadEngineShaders()
		{
			// Loading the Default Shader 
			// Add other Defaultr Shaders below <----
			//CHECKNULL(GetShaderLibrary()->LoadShader("StandardShader", "Assets\\vertexShader01.glsl", "Assets\\fragmentShader01.glsl"));

		}

		void RenderManager::BeginScene()
		{
			// Load All object in the scene 

			// First Make sure we have the correct Camera
			// Loop through all the cmaera to check if it thes corrrect one and store that index for easier access later
			// 
			// For now its just One camera
			m_mainCameraIndex = 0;



			SharedPtr<GameObjectRegistry> objRegistry = Application::GetCurrent().GetObjectLibrary();

			// Loop through all the Gameobjects in the current scene 
			for (auto& itr : objRegistry->Get())
			{
				Transform objtransform = itr.second->m_transform;
				SharedPtr<Mesh> objMesh = itr.second->m_rendermesh;

			}

		}


		void RenderManager::Init()
		{
			// Initializing Defaults that will be reused / instanced

			// Initializing Shader Library to store all the Loaded Shaders
			m_ShaderLibrary = MakeShared<ShaderLibrary>();

			// Loading all the shaders that are default to the engine
			LoadEngineShaders();


			GLDEBUG(glEnable(GL_DEPTH_TEST));
			GLDEBUG(glEnable(GL_STENCIL_TEST));
			GLDEBUG(glEnable(GL_CULL_FACE));
		
			


		}

		void RenderManager::RenderFrame()
		{
			// We gather all the Objects in the Scene and Push the mto the Render Queue
			BeginScene();


			GLDEBUG(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
			GLDEBUG(glClear(GL_COLOR_BUFFER_BIT));



		}


		SharedPtr<ShaderLibrary>& RenderManager::GetShaderLibrary()
		{
			return m_ShaderLibrary;
		}
	}
}