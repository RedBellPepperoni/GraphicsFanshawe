#pragma once

#include <string>


struct GLFWwindow;

namespace FanshaweGameEngine
{
	namespace Rendering 
	{
		class Window
		{
		protected:


			int width;
			int height;
			std::string title;
			float ratio;



		public:

			Window();
			Window(int windowWidth, int windowHeight, const std::string& windowTitle);

			~Window();
			void UpdateViewPort();
			void PollEvents();

			void Initialize();

			bool isOpen();

			void SwapBuffers();

			void CloseWindow();

			float GetAspectRatio() { return ratio; };

			GLFWwindow* windowHandle;


		};
	}
}


