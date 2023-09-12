#include "Application.h"


Application::Application()
{
	window = new Window();
	
}





void Application::RenderObjects()
{


	renderer.RenderFrame();


}

void Application::Create()
{
	

}



void Application::Run()
{
	isRunning = true;

	// Render Loop

	while (window->isOpen())
	{
		
		// Update window and listen and process window events
		window->Update();

		// Render all the vertices in the current Render array
		RenderObjects();
		
		window->SwapBuffers();

	}

	window->CloseWindow();
}
