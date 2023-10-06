#pragma once
#include <stdint.h>

namespace FanshaweGameEngine
{
	namespace Rendering
	{
		class VertexBuffer;

		class VertexArray
		{
		private:

			// Handle Id for the buffer
			uint32_t bufferId = 0;

		public:

			VertexArray();
			~VertexArray();


			void Bind();
			void UnBind();

			void FreeArray();

			void AddVertexAttributelayout(VertexBuffer& buffer, uint32_t shaderId);




		};
	}
}

