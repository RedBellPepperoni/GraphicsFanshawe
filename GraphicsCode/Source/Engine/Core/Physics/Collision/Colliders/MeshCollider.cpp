#include "MeshCollider.h"
#include "Engine/Core/Rendering/Definitions.h"
#include "Engine/Core/Physics/PhysicsEngine/Rigidbody3D.h"

namespace FanshaweGameEngine
{


	


	namespace Physics
	{

	

		MeshCollider::MeshCollider()
		{
			m_HalfDimensions = glm::vec3(0.5f, 0.5f, 0.5f);
			m_type = ColliderType::MESH;
			m_normallist.resize(3);
		}

		MeshCollider::~MeshCollider()
		{
		}

		void MeshCollider::BuildFromMesh(Mesh* mesh)
		{
			m_Hull = MakeShared<ConvexHull>();

			auto vertexBuffer = mesh->GetVBO();
			
			
			std::vector<Rendering::Vertex> vertices = mesh->GetVertexData();
			std::vector<uint32_t> indices = mesh->GetIndexData();

			int indexCount = indices.size();

			for (Rendering::Vertex vert: vertices)
			{
				m_Hull->AddVertex(vert.position);
			}

			for (size_t i = 0; i < indexCount; i += 3)
			{
				glm::vec3 n1 = vertices[indices[i]].normal;  
				glm::vec3 n2 = vertices[indices[i + 1]].normal;
				glm::vec3 n3 = vertices[indices[i + 2]].normal;
				glm::vec3 normal = n1 + n2 + n3;
				normal = glm::normalize(normal);

				int vertexIdx[] = { (int)indices[i], (int)indices[i + 1], (int)indices[i + 2] };
				m_Hull->AddFace(normal, 3, vertexIdx);
			}

			m_edgelist.resize(m_Hull->GetNumEdges());

		}

		std::vector<Vector3>& MeshCollider::GetCollisionNormals(const RigidBody3D* body)
		{
			Matrix3 objOrientation = QuatToMatrix(body->GetRotation());
			m_normallist[0] = (objOrientation * glm::vec3(1.0f, 0.0f, 0.0f)); // X - Axis
			m_normallist[1] = (objOrientation * glm::vec3(0.0f, 1.0f, 0.0f)); // Y - Axis
			m_normallist[2] = (objOrientation * glm::vec3(0.0f, 0.0f, 1.0f)); // Z - Axis
		
			return m_normallist;
		
		}

		std::vector<ColliderEdge>& MeshCollider::GetEdgeList(const RigidBody3D* body)
		{
			// TODO: insert return statement here
			Matrix4 transform = body->GetTransform() * m_transform;
			for (unsigned int i = 0; i < m_Hull->GetNumEdges(); ++i)
			{
				const HullEdge& edge = m_Hull->GetEdge(i);
				glm::vec3 A = transform * glm::vec4(m_Hull->GetVertex(edge.vStart).pos, 1.0f);
				glm::vec3 B = transform * glm::vec4(m_Hull->GetVertex(edge.vEnd).pos, 1.0f);

				m_edgelist[i] = { A, B };
			}

			return m_edgelist;
		}

		void MeshCollider::GetMinMaxFromAxis(const RigidBody3D* body, const Vector3& axis, Vector3* outMin, Vector3* outMax)
		{

			Matrix4 wsTransform = Transpose(body ? body->GetTransform() * m_transform : m_transform);
			const glm::vec3 local_axis = wsTransform * glm::vec4(axis, 1.0f);

			int vMin, vMax;

			m_Hull->GetMinMaxVerticesInAxis(local_axis, &vMin, &vMax);

			if (outMin)
				*outMin = wsTransform * glm::vec4(m_Hull->GetVertex(vMin).pos, 1.0f);
			if (outMax)
				*outMax = wsTransform * glm::vec4(m_Hull->GetVertex(vMax).pos, 1.0f);
		}

	}

}