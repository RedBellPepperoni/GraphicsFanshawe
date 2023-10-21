#include "Application.h"
#include "Engine/Utils/Logging/Log.h"

// Forward Delacration Headers
#include "Engine/Core/System/Window/Window.h"
#include "Engine/Core/Resources/ResourceManager.h"
#include "Engine/Core/Macros/Macro.h"
#include "Engine/Core/ECS/Object/GameObject.h"
#include "Engine/Core/Rendering/Renderer/RenderManager.h"
#include "Engine/Core/Rendering/Essentials/Camera.h"


namespace FanshaweGameEngine
{
	Application* Application::m_currentApplication = nullptr;

	Application::Application()
	{
		if (m_currentApplication != nullptr)
		{
			printf("Application Instance already exists");
			return;
		}

		// initializing the Logging
		Debug::Log::OnInit();

		// Creating and Initializing the Open GL Window
		m_window = MakeUnique<Window>();
		m_window->Initialize();

		// Initializing teh Render manager
		m_renderManager = MakeUnique<RenderManager>();

		m_renderManager->Init();

		// Setting up teh Model and Object Library
		m_modelLibrary   = MakeShared<ModelLibrary>();
		m_objectRegistry = MakeShared<GameObjectRegistry>();


		// Setting the Instance reference of the creatd application
		m_currentApplication = this;
		

		// Activate the User function
		OnCreate();



	}





	void Application::RenderObjects()
	{
		// Tell the Render Manager to Do Drawing
		m_renderManager->RenderFrame();

	}



	Application::~Application()
	{
	}

	Application& Application::GetCurrent()
	{
		return *m_currentApplication;
	}

	Window& Application::GetWindow()
	{
		return *m_window;
	}

	void Application::Initialize()
	{
		
	
		// Calling Init on the child applications

		// Add loading the scene here

		OnInit();
	}

	void Application::Run()
	{
		m_isRunning = true;

		// Render Loop

		while (m_window->isOpen())
		{

			// Update window and listen and process window events
			m_window->UpdateViewPort();

			// Render all the vertices in the current Render array
			RenderObjects();

			m_window->SwapBuffers();
			m_window->PollEvents();


		}

		m_window->CloseWindow();
	}

	UniquePtr<RenderManager>& Application::GetRenderManager()
	{
		return m_renderManager;
	}

	

	SharedPtr<ModelLibrary>& Application::GetModelLibrary()
	{
		return m_modelLibrary;
	}

	
	
	SharedPtr<GameObjectRegistry>& Application::GetObjectLibrary()
	{
		return m_objectRegistry;
	}
	std::vector<SharedPtr<Camera>>& Application::GetSceneCameras()
	{
		return m_scenecameras;
	}
}
