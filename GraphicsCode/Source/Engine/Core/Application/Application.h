#pragma once
#include "Engine/Core/Memory/Memory.h"
#include <vector>



namespace FanshaweGameEngine
{


	// Forward Declaration

	class ModelLibrary;
	class GameObjectRegistry;
	class Scene;

	namespace Rendering
	{
		class Window;
		class RenderManager;
		class Camera;
    }



using Rendering::RenderManager;
using Rendering::Window;
using Rendering::Camera;



	class Application
	{

	protected:

		// The reference to the current application -> there should only be one instance
		static Application* m_currentApplication;

		// The Manager which controls all the Rendering of the Applciation
		UniquePtr<RenderManager> m_renderManager;

		UniquePtr<Window> m_window = nullptr;


		bool m_isRunning = false;

		// Right now it points to the class given by M Feeney, change this later
		//SharedPtr<ShaderLibrary> shaderLibrary;

	    // The  containers for the loaded models 
		SharedPtr<ModelLibrary> m_modelLibrary;		

		// Pointer to the currently loaded scene
		SharedPtr<Scene> m_currentScene;

		

	protected:

		// Render all the Objects in the scene
		void RenderObjects();

		// Teh Constructor
		Application();

		// Inherited class methods to do stuff
		virtual void OnCreate(){};
		virtual void OnUpdate(){};
		virtual void OnInit()  {};


		

	public:


		// Destructor
		virtual ~Application();

		// Reference Getter for the application
		static Application& GetCurrent();

		// Referene getter for the current window
		Window& GetWindow();

		// Reference Getter for teh current scene
		Scene* GetCurrentScene() const;

		// The start up setup for the apllication
		void Initialize();

		// This methods initaitzes the runtime and starts the gameloop
		void Run();


		// Reference Getters to the renderManager
		UniquePtr<RenderManager>& GetRenderManager();

		// Reference getter to teh Model Library
		SharedPtr<ModelLibrary>& GetModelLibrary();
		

		

	};
}

