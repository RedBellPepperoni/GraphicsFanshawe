#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer
{

private:

	unsigned int id;
	size_t byteSie;

public:

	VertexBuffer();

	~VertexBuffer();

	void Bind();
	void UnBind();

	void Load();



};

