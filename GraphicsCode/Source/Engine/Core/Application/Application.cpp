#include "Application.h"
#include "Engine/Utils/Logging/Log.h"

// Forward Delacration Headers
#include "Engine/Core/System/Window/Window.h"
#include "Engine/Core/Resources/ResourceManager.h"
#include "Engine/Core/Macros/Macro.h"
#include "Engine/Core/ECS/Object/GameObject.h"


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

		


		m_window = MakeUnique<Window>();

		m_window->Initialize();

		
		m_modelLibrary   = MakeShared<ModelLibrary>();
		//m_objectRegistry = MakeShared<GameObjectRegistry>();


		m_currentApplication = this;
		

		OnCreate();



	}





	void Application::RenderObjects()
	{


		// m_renderManager->DrawFrame();


	}

	void Application::LoadStuff()
	{
		
		//m_renderer->LoadMeshToPipeline(bunnyMesh);

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
		// initializing the Logging
		Debug::Log::OnInit();
	
		// Calling Init on the child applications
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
	SharedPtr<ModelLibrary>& Application::GetModelLibrary()
	{
		return m_modelLibrary;
	}
	
	/*SharedPtr<GameObjectRegistry>& Application::GetObjectLibrary()
	{
		return m_objectRegistry;
	}*/
}
