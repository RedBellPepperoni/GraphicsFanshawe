#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>


class Window
{
protected:
	


	GLuint vertex_buffer, vertex_shader, fragment_shader, program;
	GLint mvp_location, vpos_location, vcol_location;

	int width;
	int height;
	std::string title;

	
	

public:
	
	Window();
	Window(int windowWidth, int windowHeight, const std::string& windowTitle);

	~Window();
	void Update();

	void Initialize();

	bool isOpen();

	void SwapBuffers();

	void CloseWindow();

	GLFWwindow* windowHandle;


};

