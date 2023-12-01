#pragma once
#include <stdint.h>
#include "VertexAttribute.h"
#include <vector>

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


			void Bind() const;
			void UnBind() const ;

			void FreeArray();

			void AddVertexAttributelayout(/*VertexBuffer& buffer,*/ uint32_t shaderId);
			void AddVertexAttribLayout(std::vector<VertexAttribute>& layout);
			//void RemoveVertexAttribLayout(std::vector<VertexAttribute>& layout); 

		};
	}
}

