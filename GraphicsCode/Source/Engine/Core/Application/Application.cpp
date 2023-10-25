#include "Application.h"
#include "Engine/Utils/Logging/Log.h"
#include "Engine/Utils/Time/Time.h"
#include "Engine/Core/System/Input/InputSystem.h"
// Forward Delacration Headers
#include "Engine/Core/System/Window/Window.h"

#include "Engine/Core/Scene/Scene.h"
#include "Engine/Core/Resources/ResourceManager.h"
#include "Engine/Core/Macros/Macro.h"
//#include "Engine/Core/ECS/Object/GameObject.h"
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
		//m_objectRegistry = MakeShared<GameObjectRegistry>();

		m_currentScene = MakeShared<Scene>("testScene");

		

		// Setting the Instance reference of the creatd application
		m_currentApplication = this;
		
		// Activate the User function
		OnCreate();

		

	}

	void Application::UpdateDeltaTime(float& lastFrameEnd, float& lastSecondEnd, size_t& fps)
	{

		float currentTime = Time::CurrentEngineTime();

		if (m_isPaused)
		{
			lastFrameEnd = 0.0f;
			lastSecondEnd = 0.0f;
			fps = 0;
			m_Fps = 0;
			m_deltaTime = 0;
		}

		else
		{
			fps++;

			if (lastFrameEnd - lastSecondEnd >= 1.0f)
			{
				m_Fps = fps;
				lastSecondEnd = currentTime;
				fps = 0;

			}

			m_deltaTime = m_timeScale * (currentTime - lastFrameEnd);
			m_totalElapsedTime += m_deltaTime;
		}

		lastFrameEnd = currentTime;

	}





	void Application::RenderObjects()
	{
		// Tell the Render Manager to Do Drawing
		m_renderManager->ProcessScene(GetCurrentScene());


		m_renderManager->RenderFrame();

	}



	Application::~Application()
	{

		
	}


	Application& Application::GetCurrent()
	{
		return *m_currentApplication;
	}

	Window* Application::GetAppWindow()
	{
		return m_window.get();
	}

	Scene* Application::GetCurrentScene() const
	{
		return m_currentScene.get();
	}

	void Application::Initialize()
	{
		
		this->m_window->SetEventCallback(BIND_FN(Application::ProcessEvent));

		// Calling Init on the child applications
		OnInit();
	}

	void Application::Run()
	{
		m_isRunning = true;

		float secondEnd = Time::CurrentEngineTime();
		float frameEnd = Time::CurrentEngineTime();
		size_t frames = 0;



		// Render Loop

		while (m_window->isOpen())
		{

			UpdateDeltaTime(frameEnd, secondEnd, frames);
			m_window->PollEvents();
			

			// Update window and listen and process window events
			m_window->UpdateViewPort();

			// Render all the vertices in the current Render array
			RenderObjects();

			m_window->SwapBuffers();
			
			
			OnUpdate();


		}

		m_window->CloseWindow();
	}

	void Application::ProcessEvent(EventBase& event)
	{
		EventDispatcher dispatcher(event);

		// Event already handled
		if (event.GetHandled()) { return; }

		Input::InputSystem::GetInstance().ProcessEvent(event);
	}

	UniquePtr<RenderManager>& Application::GetRenderManager()
	{
		return m_renderManager;
	}

	

	SharedPtr<ModelLibrary>& Application::GetModelLibrary()
	{
		return m_modelLibrary;
	}

	float Application::GetGLFWTime()
	{
		return m_window->GetGLFWTime();
	}

	float Application::GetTotalElapsed() const
	{
		return m_totalElapsedTime;
	}

	void Application::SetTotalElapsed(float time)
	{
		m_totalElapsedTime = time > 0.0f ? time : 0.0f;
	}

	float Application::GetDelta() const
	{
		return m_deltaTime;
	}

	float Application::GetUnscaledDelta() const
	{
		return m_deltaTime / m_timeScale;
	}

	size_t Application::GetFPS() const
	{
		return m_Fps;
	}

	const int Application::GetMainCameraIndex() const
	{
		return m_mainCameraIndex;
	}

	void Application::SetMainCameraIndex(const int newIndex)
	{
		/*size_t count = GetCurrentScene()->GetRegistry().view<Camera>().size();

		int index = newIndex;

		if (newIndex > count)
		{
			LOG_WARN("Out of bound index for camera");

			index = 0;
		}


		m_mainCameraIndex = index;*/
	}

	/*void Application::SetCursorPosition(Vector2 position)
	{
		m_window->SetMousePosition(position);
	}

	void Application::SetCursorHidden(bool hidden)
	{
		m_window->SetMouseHidden(hidden);
	}*/

	
	
	
	

}