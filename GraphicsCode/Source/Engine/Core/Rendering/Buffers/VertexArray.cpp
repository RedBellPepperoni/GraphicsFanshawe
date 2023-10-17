#include "VertexArray.h"
#include "Engine/Core/Rendering/Definitions.h"
#include "VertexBuffer.h"

namespace FanshaweGameEngine
{

	namespace Rendering
	{
		VertexArray::VertexArray()
		{
			GLDEBUG(glGenVertexArrays(1, &bufferId));

		}
		VertexArray::~VertexArray()
		{
			FreeArray();
		}

		void VertexArray::Bind()
		{
			GLDEBUG(glBindVertexArray(bufferId));

		}
		void VertexArray::UnBind()
		{
			GLDEBUG(glBindVertexArray(0));

		}


		void VertexArray::FreeArray()
		{
			if (bufferId != 0)
			{
				GLDEBUG(glDeleteVertexArrays(1, &bufferId));
			}

			bufferId = 0;
		}


		void VertexArray::AddVertexAttributelayout(uint32_t shaderId)
		{

			// Should Make this Dynamic later on, actually store the atrribs in the shader itslef and pull data accordingly

			GLint position = GLDEBUG(glGetAttribLocation(shaderId, "vPosition"));	// program
			GLint color = GLDEBUG(glGetAttribLocation(shaderId, "vColor"));

			GLDEBUG(glEnableVertexAttribArray(position));
			GLDEBUG(glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, Vertex::Stride, (void*)offsetof(Vertex, position)));


			GLDEBUG(glEnableVertexAttribArray(color));
			GLDEBUG(glVertexAttribPointer(color, 4, GL_FLOAT, GL_FALSE, Vertex::Stride, (void*)offsetof(Vertex, color)));

		}
	}
}