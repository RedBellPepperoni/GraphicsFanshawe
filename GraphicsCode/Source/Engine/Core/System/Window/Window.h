#pragma once
#include "Engine/Core/System/Events/Event.h"
#include <functional>
#include <string>
#include "Engine/Utils/Math.h"
#include "Engine/Utils/GLUtils.h"


namespace FanshaweGameEngine
{
	namespace Rendering 
	{
		


		class Window
		{
		public:

			using EventCallBackFn = std::function<void(EventBase&)>;

			struct WindowProperties
			{

				int width;
				int height;
				std::string title;
				float aspectRatio;
				EventCallBackFn eventHandler;
			};
			

			

		protected:


			GLFWwindow* windowHandle;
			

			WindowProperties m_properties;
			


			// ============================ EVENT WRAPPERS  ==========================

			static inline void WindowSizeCallback(GLFWwindow* window, int newWidth, int newHeight);

			static inline void WindowCloseCallback(GLFWwindow* window);

			static inline void WindowFocusCallback(GLFWwindow* window, int focus);

			static inline void WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

			static inline void WindowMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

			static inline void WindowMouseScrollCallback(GLFWwindow* window, double xDelta, double yDelta);

			static inline void WindowCursorCallback(GLFWwindow* window, double xPos, double yPos);


		public:

			

			Window();
			Window(const WindowProperties& properties);



			~Window();
			void UpdateViewPort();


			void PollEvents();

			void SetEventCallback(const EventCallBackFn& callback);

			void CallEvent(EventBase& event);

			void Initialize();

			bool isOpen();

			void SwapBuffers();

			void CloseWindow();

			float GetAspectRatio() { return m_properties.aspectRatio; };

			float GetGLFWTime() const;

			void SetWindowTitle(const std::string& newTitle);

			
			void SetMousePosition(Vector2 position);
			void SetMouseHidden(bool isHidden);

		};
	}
}


