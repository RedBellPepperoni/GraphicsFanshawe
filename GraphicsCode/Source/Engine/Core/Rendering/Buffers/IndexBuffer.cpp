#include "IndexBuffer.h"
#include "Engine/Core/Rendering/Definitions.h"

namespace FanshaweGameEngine
{

	namespace Rendering
	{
		IndexBuffer::IndexBuffer(size_t count, uint32_t* data, UsageType usage) : indiciesCount(count)
			, bufferUsage(usage)
		{
			// Put GL Error checking here

			// Generating and getting an ID for a new Index Buffer
			glGenBuffers(1, &bufferId);

			// Binding the Generated buffer for use
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);

			// Loading Data into the binded buffer
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GetGLBufferUsage(usage));


		}
		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &bufferId);
		}
		void IndexBuffer::Bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
		}
		void IndexBuffer::UnBind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		size_t IndexBuffer::GetIndiciesCount()
		{
			return indiciesCount;
		}
	}
}