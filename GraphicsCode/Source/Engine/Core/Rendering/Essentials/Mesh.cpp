#include "Mesh.h"
#include "Engine/Utils/Loading/ModelLoader.h"
#include "Engine/Core/Resources/ResourceManager.h"


namespace FanshaweGameEngine
{
	namespace Rendering
	{
		Mesh::Mesh()
			: m_vertices()
			, m_indicies()
			, m_VBO(nullptr)
			, m_IBO(nullptr)
			, m_meshName("empty")
		{
		}

		Mesh::Mesh(const Mesh& mesh)
			: m_vertices(mesh.m_vertices)
			, m_indicies(mesh.m_indicies)
			, m_VBO(mesh.m_VBO)
			, m_IBO(mesh.m_IBO)
			, m_meshName(mesh.GetName())
		{
		}

		Mesh::Mesh(const std::vector<Vertex>& inVertices, const std::vector<uint32_t>& inIndicies)
		{
			// copying the input Data into the vertex and index storage
			m_vertices = inVertices;
			m_indicies = inIndicies;

			// Calculating the total number of vertices and indices
			size_t vertexCount = m_vertices.size();
			size_t indexCount = m_indicies.size();

			// Creating a new Index buffer with the processed data
			m_IBO = Factory<IndexBuffer>::Create(indexCount, m_indicies.data(), UsageType::STATIC_DRAW);

			// Creating a new vertex buffer with the processed data
			m_VBO = Factory<VertexBuffer>::Create(sizeof(Vertex) * vertexCount, m_vertices.data(), UsageType::STATIC_DRAW);
		}

		// Default Constructor
		Mesh::~Mesh()
		{

		}

		void Mesh::SetName(const std::string& newName)
		{
			m_meshName = newName;
		}
		const std::string& Mesh::GetName() const
		{
			return m_meshName;
		}
		const std::vector<Vertex>& Mesh::GetVertexData() 
		{
			return m_vertices;
		}
		const std::vector<uint32_t>& Mesh::GetIndexData() 
		{
			return m_indicies;
		}

		SharedPtr<VertexBuffer>& Mesh::GetVBO() 
		{
			return m_VBO;
		}
		 SharedPtr<IndexBuffer>& Mesh::GetIBO() 
		{
			return m_IBO;
		}
		
	}
}

