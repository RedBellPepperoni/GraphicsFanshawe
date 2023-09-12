#include "Renderer.h"
#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Renderer::DrawVertices(size_t vertexOffset, size_t vertexCount)
{
	// Drawing all the vertices in tthe Vertex buffer
	glDrawArrays(GL_TRIANGLES, vertexOffset, vertexCount);
	
}



void Renderer::RenderFrame()
{
	/// Load All objects in vertex Buffers


	/// Then Draw the vertices in buffer
	DrawVertices(0,3);
}
