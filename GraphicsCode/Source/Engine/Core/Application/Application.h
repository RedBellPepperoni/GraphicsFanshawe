#pragma once
#include "Engine/Core/Memory/Memory.h"
#include <vector>



namespace FanshaweGameEngine
{


	// Forward Declaration

	class ModelLibrary;
	class GameObjectRegistry;


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


		std::vector<SharedPtr<Camera>> m_scenecameras;


		bool m_isRunning = false;

		// Right now it points to the class given by M Feeney, change this later
		//SharedPtr<ShaderLibrary> shaderLibrary;

	
		SharedPtr<ModelLibrary> m_modelLibrary;		
		SharedPtr<GameObjectRegistry> m_objectRegistry;
		

	protected:

		void RenderObjects();


		Application();

		virtual void OnCreate(){};
		virtual void OnUpdate(){};
		virtual void OnInit()  {};


	public:




		virtual ~Application();
		static Application& GetCurrent();
		Window& GetWindow();


		void Initialize();
		void Run();

		UniquePtr<RenderManager>& GetRenderManager();

		SharedPtr<ModelLibrary>& GetModelLibrary();
		
		SharedPtr<GameObjectRegistry>& GetObjectLibrary();

		std::vector<SharedPtr<Camera>>& GetSceneCameras();

	};
}

