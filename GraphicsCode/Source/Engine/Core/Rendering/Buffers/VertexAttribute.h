#pragma once
#include <cstddef>
#include <cstdint>

namespace FanshaweGameEngine
{

	namespace Rendering
	{

		struct VertexAttribute
		{
			uint32_t type;
			uint16_t components;
			uint16_t entries;
			size_t byteSize;

			template<typename T>
			static VertexAttribute Attribute();

		};

	}
}

