#pragma once

#define NOMINMAX
// Windows API
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


namespace FanshaweGameEngine
{

#ifdef _DEBUG
	// We are in Debug mode, so we can use the GL error checking
#define GLDEBUG(func) func; glCheckError_(__FILE__, __LINE__) 
#else
	// Otherwise just Let it Be
#define GLDEBUG(func) func;
#endif // _DEBUG

	// Taken from https://learnopengl.com/In-Practice/Debugging
	GLenum glCheckError_(const char* file, int line);
	


}