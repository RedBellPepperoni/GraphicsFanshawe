#pragma once
#include <memory>
#include "Window.h"
#include "Renderer.h"

class Application
{
private:

	static Application* currentApplication;
	Renderer renderer;

	Window* window;
	bool isRunning = false;


private:

	void RenderObjects();

	void Create();


protected:

	
	
   

public:

	Application();

	void Run();


};

