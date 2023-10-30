#pragma once
#include "Engine/Core/Memory/Memory.h"
#include "Engine/Core/System/Events/Event.h"
#include "Engine/Utils/Math.h"
#include <vector>
#include <string>



namespace FanshaweGameEngine
{


	// Forward Declaration



	class ModelLibrary;
	class GameObjectRegistry;
	class Scene;
//
	namespace Rendering
	{
		class Window;
		class RenderManager;
		class Camera;
    }

	namespace Physics
	{
		class PhysicsEngine;
	}


using Rendering::RenderManager;
using Rendering::Window;
using Rendering::Camera;


using Physics::PhysicsEngine;

	class Application
	{

	protected:

		// The reference to the current application -> there should only be one instance
		static Application* m_currentApplication;

		// The Manager which controls all the Rendering of the Applciation
		UniquePtr<RenderManager> m_renderManager;

		UniquePtr<Window> m_window = nullptr;

		//UniquePtr<PhysicsEngine> m_physicsSystem = nullptr;


		bool m_isRunning = false;
		bool m_isPaused = false;

		// Right now it points to the class given by M Feeney, change this later
		//SharedPtr<ShaderLibrary> shaderLibrary;

	    // The  containers for the loaded models 
		SharedPtr<ModelLibrary> m_modelLibrary;		

		// Pointer to the currently loaded scene
		SharedPtr<Scene> m_currentScene;

		// Default Scale
		float m_timeScale = 1.0f;

		float m_deltaTime = 0.0f;
		float m_totalElapsedTime = 0.0f;
		size_t m_Fps = 0;


		// Future case when there can be multiple cameras // 
					// "-1"  means no rendering cameras were found
		int m_mainCameraIndex = -1;
		

	protected:

		// Render all the Objects in the scene
		void RenderObjects();

		// Teh Constructor
		Application();

		// Inherited class methods to do stuff
		virtual void OnCreate(){};
		virtual void OnUpdate(float deltaTime) {};
		virtual void OnInit()  {};

		void UpdateDeltaTime(float& lastFrameEnd, float& lastSecondEnd, size_t& fps);
		

	public:


		// Destructor
		virtual ~Application();

		// Reference Getter for the application
		static Application& GetCurrent();

		// Referene getter for the current window
		Window* GetAppWindow();

		// Reference Getter for teh current scene
		Scene* GetCurrentScene() const;

		// The start up setup for the apllication
		void Initialize();

		// This methods initaitzes the runtime and starts the gameloop
		void Run();


		// Deals with the Event queue to be processed by the glfw runtime
		void ProcessEvent(EventBase& event);

		// Reference Getters to the renderManager
		UniquePtr<RenderManager>& GetRenderManager();

		// Reference getter to teh Model Library
		SharedPtr<ModelLibrary>& GetModelLibrary();
		
		// Returns the GLFW current time from the current glfwwindow
		float GetGLFWTime();
		
		float GetTotalElapsed() const;
		void SetTotalElapsed(float time);
		float GetDelta() const;
		float GetUnscaledDelta() const;

		size_t GetFPS() const;

		const int GetMainCameraIndex() const;
		void SetMainCameraIndex(const int newIndex);

		void SetCursorPosition(Vector2 position);
		void SetCursorHidden(bool hidden);

		void SetWindowTitle(const std::string& newTitle);


	};
}

