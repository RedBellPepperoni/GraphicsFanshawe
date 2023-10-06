#include "VertexArray.h"
#include "Engine/Core/Rendering/Definitions.h"
#include "VertexBuffer.h"

namespace FanshaweGameEngine
{

	namespace Rendering
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &bufferId);

		}
		VertexArray::~VertexArray()
		{
			FreeArray();
		}
		void VertexArray::Bind()
		{
			glBindVertexArray(bufferId);
		}
		void VertexArray::UnBind()
		{
			glBindVertexArray(0);

		}


		void VertexArray::FreeArray()
		{
			if (bufferId != 0)
			{
				glDeleteVertexArrays(1, &bufferId);
			}

			bufferId = 0;
		}
		void VertexArray::AddVertexAttributelayout(VertexBuffer& buffer, uint32_t shaderId)
		{
			Bind();
			buffer.Bind();

			GLint vposlocation = glGetAttribLocation(shaderId, "vPos");	// program
			GLint vcollocation = glGetAttribLocation(shaderId, "vCol");	// program;
			GLint vNormallocation = glGetAttribLocation(shaderId, "vNormal");	// program;

			glEnableVertexAttribArray(vposlocation);
			glVertexAttribPointer(vposlocation,
				4,
				GL_FLOAT,
				GL_FALSE,
				sizeof(Vertex),
				(void*)offsetof(Vertex, position));

			glEnableVertexAttribArray(vcollocation);
			glVertexAttribPointer(vcollocation,
				4,
				GL_FLOAT,
				GL_FALSE,
				sizeof(Vertex),
				(void*)offsetof(Vertex, color));

			glEnableVertexAttribArray(vposlocation);
			glVertexAttribPointer(vposlocation,
				4,
				GL_FLOAT,
				GL_FALSE,
				sizeof(Vertex),
				(void*)offsetof(Vertex, normal));


		}
	}
}