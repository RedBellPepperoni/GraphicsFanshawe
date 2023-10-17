#pragma once
#include "Engine/Utils/Math.h"
#include "Engine/Utils/GLUtils.h"


namespace FanshaweGameEngine
{

	using namespace Math;

	namespace Rendering
	{
		enum class UsageType
		{
			STREAM_DRAW,
			STREAM_READ,
			STREAM_COPY,
			STATIC_DRAW,
			STATIC_READ,
			STATIC_COPY,
			DYNAMIC_DRAW,
			DYNAMIC_READ,
			DYNAMIC_COPY,
		};

		enum class BufferType
		{
			UNKNOWN = 0,
			ARRAY,
			ELEMENT_ARRAY,
			SHADER_STORAGE,
		};

		// Returns the correct GL value for the usage
		static uint32_t GetGLBufferUsage(UsageType usage)
		{
			switch (usage)
			{
			case UsageType::STREAM_DRAW: return GL_STREAM_DRAW;
				break;
			case UsageType::STREAM_READ: return GL_STREAM_READ;
				break;
			case UsageType::STREAM_COPY: return GL_STREAM_COPY;
				break;
			case UsageType::STATIC_DRAW: return GL_STATIC_DRAW;
				break;
			case UsageType::STATIC_READ: return GL_STATIC_READ;
				break;
			case UsageType::STATIC_COPY: return GL_STATIC_COPY;
				break;
			case UsageType::DYNAMIC_DRAW: return GL_DYNAMIC_DRAW;
				break;
			case UsageType::DYNAMIC_READ: return GL_DYNAMIC_READ;
				break;
			case UsageType::DYNAMIC_COPY: return GL_DYNAMIC_COPY;
				break;
			default: return GL_FALSE;
				break;
			}
		}

		struct Vertex
		{
			Vertex() : position(Math::Vector3(0.0f))
				, color(Math::Vector4(0.0f))
				, normal(Math::Vector3(0.0f))
			{

			}

			Vector3 position;
			Vector4 color;
			Vector3 normal;


			static const size_t Stride = sizeof(Vector3) + sizeof(Vector4) + sizeof(Vector3);
		};

		struct Triangle
		{
			Vertex v0;
			Vertex v1;
			Vertex v2;
		};
		

	}
}