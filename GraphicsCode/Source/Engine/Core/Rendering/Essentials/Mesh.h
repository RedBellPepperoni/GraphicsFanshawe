#pragma once
#include "Engine/Core/Rendering/Buffers/VertexBuffer.h"
#include "Engine/Core/Rendering/Buffers/IndexBuffer.h"
#include "Engine/Core/Memory/Memory.h"

#include "Engine/Core/Rendering/Definitions.h"
#include <vector>
#include <string>

namespace FanshaweGameEngine
{

	namespace Rendering
	{
		// Namespace Stuff
		
		
		// The actual Drawable Mesh

		class Mesh
		{

		protected:

			std::string m_meshName;

			// Storage for vertices and indicies for the Mesh
			std::vector<Vertex> m_vertices;
			std::vector<uint32_t> m_indicies;

			// The Buffers that are needed for OpenGL
			SharedPtr<VertexBuffer> m_VBO;
			SharedPtr<IndexBuffer> m_IBO;


			uint32_t m_vertexCount;
			uint32_t m_indiciesCount;
			
			


		public:

			Mesh();
			Mesh(const Mesh& mesh);
			Mesh(const std::vector<Vertex>& inVertices, const std::vector<uint32_t>& inIndicies);

			~Mesh();

			// Change/Set the name of a mesh
			void SetName(const std::string& newName);

			// Getter for accessing the mesh's name
			const std::string& GetName() const;


			// Getters for Vertex and Index data
			const std::vector<Vertex>& GetVertexData();
			const std::vector<uint32_t>& GetIndexData();

			const uint32_t GetIndexCount();

			// Getters for Vertex and Index buffers
			SharedPtr<VertexBuffer>& GetVBO();
			SharedPtr<IndexBuffer>& GetIBO();

			

		};
	}
}

