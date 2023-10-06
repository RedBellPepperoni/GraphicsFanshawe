#pragma once
#include "Engine/Utils/GLUtils.h"
#include <string>

namespace FanshaweGameEngine
{
	namespace Rendering 
	{
		class Window
		{
		protected:



			GLuint vertex_buffer, vertex_shader, fragment_shader, program;


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


