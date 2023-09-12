#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::UnBind()
{ 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Load()
{
}
