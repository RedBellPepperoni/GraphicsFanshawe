#include "BoxCollider.h"
#include "Engine/Core/Physics/PhysicsEngine/Rigidbody3D.h"


namespace FanshaweGameEngine
{
	namespace Physics
	{

		SharedPtr<ConvexHull> BoxCollider::m_CubeHull = MakeShared<ConvexHull>();
		
		BoxCollider::BoxCollider()
		{
			m_CuboidHalfDimensions = Vector3(0.5f, 0.5f, 0.5f);
			m_type = ColliderType::BOX;
			m_transform = Scale(Matrix4(1.0), m_CuboidHalfDimensions);

			if (m_CubeHull->GetNumVertices() == 0)
			{
				ConstructCubeHull();
			}

			m_normallist.resize(3);
			m_edgelist.resize(m_CubeHull->GetNumEdges());
		}
		BoxCollider::BoxCollider(const Vector3& halfDims)
		{
			m_CuboidHalfDimensions = halfDims;
			m_type = ColliderType::BOX;
			m_transform = Scale(Matrix4(1.0), halfDims);

			if (m_CubeHull->GetNumVertices() == 0)
			{
				ConstructCubeHull();
			}

			m_normallist.resize(3);
			m_edgelist.resize(m_CubeHull->GetNumEdges());
		}
		BoxCollider::~BoxCollider()
		{
		}
		std::vector<Vector3>& BoxCollider::GetCollisionNormals(const RigidBody3D* currentBody)
		{
			// TODO: insert return statement here
			m_normallist.resize(3);

			Matrix3 objOrientation = glm::toMat3(currentBody->GetRotation());   //.RotationMatrix();
			m_normallist[0] = (objOrientation * Vector3(1.0f, 0.0f, 0.0f)); // X - Axis
			m_normallist[1] = (objOrientation * Vector3(0.0f, 1.0f, 0.0f)); // Y - Axis
			m_normallist[2] = (objOrientation * Vector3(0.0f, 0.0f, 1.0f)); // Z - Axis
		

			return m_normallist;
		}


		std::vector<ColliderEdge>& BoxCollider::GetEdgeList(const RigidBody3D* currentBody)
		{
			// TODO: insert return statement here
			Matrix4 transform = currentBody->GetTransform() * m_transform;
			for (unsigned int i = 0; i < m_CubeHull->GetNumEdges(); ++i)
			{
				const HullEdge& edge = m_CubeHull->GetEdge(i);
				Vector3 A = transform * Vector4(m_CubeHull->GetVertex(edge.vStart).pos, 1.0f);
				Vector3 B = transform * Vector4(m_CubeHull->GetVertex(edge.vEnd).pos, 1.0f);

				m_edgelist[i] = { A, B };
			}

			return m_edgelist;
		}
		void BoxCollider::GetMinMaxFromAxis(const RigidBody3D* body, const Vector3& axis, Vector3* outMin, Vector3* outMax)
		{

			Matrix4 wsTransform = body ? body->GetTransform() * m_transform : m_transform;
			const Vector3 local_axis = Transpose(wsTransform) * Vector4(axis, 1.0f);

			int vMin, vMax;

			m_CubeHull->GetMinMaxVerticesInAxis(local_axis, &vMin, &vMax);

			if (outMin)
				*outMin = wsTransform * Vector4(m_CubeHull->GetVertex(vMin).pos, 1.0f);
			if (outMax)
				*outMax = wsTransform * Vector4(m_CubeHull->GetVertex(vMax).pos, 1.0f);
		}
		void BoxCollider::ConstructCubeHull()
		{
			
			// Vertices
			m_CubeHull->AddVertex(Vector3(-1.0f, -1.0f, -1.0f)); // 0
			m_CubeHull->AddVertex(Vector3(-1.0f, 1.0f, -1.0f));  // 1
			m_CubeHull->AddVertex(Vector3(1.0f, 1.0f, -1.0f));   // 2
			m_CubeHull->AddVertex(Vector3(1.0f, -1.0f, -1.0f));  // 3

			m_CubeHull->AddVertex(Vector3(-1.0f, -1.0f, 1.0f)); // 4
			m_CubeHull->AddVertex(Vector3(-1.0f, 1.0f, 1.0f));  // 5
			m_CubeHull->AddVertex(Vector3(1.0f, 1.0f, 1.0f));   // 6
			m_CubeHull->AddVertex(Vector3(1.0f, -1.0f, 1.0f));  // 7

			int face1[] = { 0, 1, 2, 3 };
			int face2[] = { 7, 6, 5, 4 };
			int face3[] = { 5, 6, 2, 1 };
			int face4[] = { 0, 3, 7, 4 };
			int face5[] = { 6, 7, 3, 2 };
			int face6[] = { 4, 5, 1, 0 };

			// Faces
			m_CubeHull->AddFace(Vector3(0.0f, 0.0f, -1.0f), 4, face1);
			m_CubeHull->AddFace(Vector3(0.0f, 0.0f, 1.0f), 4, face2);
			m_CubeHull->AddFace(Vector3(0.0f, 1.0f, 0.0f), 4, face3);
			m_CubeHull->AddFace(Vector3(0.0f, -1.0f, 0.0f), 4, face4);
			m_CubeHull->AddFace(Vector3(1.0f, 0.0f, 0.0f), 4, face5);
			m_CubeHull->AddFace(Vector3(-1.0f, 0.0f, 0.0f), 4, face6);
		}
	}
}