#pragma once



class Renderer
{
private:
	void DrawVertices(size_t vertexCount, size_t vertexOffset);

	void LoadVertexBuffer();
	

public:

	void RenderFrame();
};

