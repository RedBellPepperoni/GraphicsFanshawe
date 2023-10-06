#pragma once
#include "Engine/Core/Memory/Memory.h"
#include "Engine/Core/Rendering/Renderer/RenderManager.h"


namespace FanshaweGameEngine
{


	// Forward Declaration

	class ModelLibrary;
	class GameObjectRegistry;


	namespace Rendering
	{
		class Window;
    }



using Rendering::RenderManager;
using Rendering::Window;



	class Application
	{

	protected:

		// The reference to the current application -> there should only be one instance
		static Application* m_currentApplication;

		// The Manager which controls all the Rendering of the Applciation
		RenderManager m_renderManager;

		UniquePtr<Window> m_window = nullptr;


		bool m_isRunning = false;

		// Right now it points to the class given by M Feeney, change this later
		//SharedPtr<ShaderLibrary> shaderLibrary;

	
		SharedPtr<ModelLibrary> m_modelLibrary;		
		SharedPtr<GameObjectRegistry> m_objectRegistry;
		

	protected:

		void RenderObjects();

		void LoadStuff();


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



		SharedPtr<ModelLibrary>& GetModelLibrary();
		
		SharedPtr<GameObjectRegistry>& GetObjectLibrary();

	};
}

