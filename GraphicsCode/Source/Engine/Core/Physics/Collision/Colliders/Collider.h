#pragma once
#include "Engine/Utils/Math.h"
#include <vector>

namespace FanshaweGameEngine
{
	namespace Physics
	{

		class RigidBody3D;

		// this is the Edge for the Collison Shape that will be used for detection 
		struct ColliderEdge
		{
			ColliderEdge(const Vector3& firstPoint = Vector3(0.0f), const Vector3& secondPoint = Vector3(0.0f))
				: firstPosition(firstPoint)
				, secondPosition(secondPoint)
			{

			}


			Vector3 firstPosition;
			Vector3 secondPosition;
			
		};


		enum ColliderType : uint8_t
		{
			None = 0,
			CuboidCollider = 1,
			SphereCollider = 2,
			CapsuleCollider = 4,
			MeshCollider = 8,
			MaxType = 16

		};

		class Collider
		{
		public:

			Collider();


			virtual ~Collider();

			void SetTransform(const Matrix4& transform);

			virtual float GetSize() const = 0;



			virtual std::vector<Vector3>& GetCollisionNormals(const RigidBody3D* currentBody) = 0;

			virtual std::vector<ColliderEdge>& GetEdgeList(const RigidBody3D* currentBody) = 0;

			virtual void GetMinMaxFromAxis(const RigidBody3D* body, const Vector3& axis, Vector3* outMin, Vector3* outMax) = 0;

			ColliderType GetType() const;

		protected:

			// type of collider
			ColliderType m_type;

			// The local transform matrix
			Matrix4 m_transform;

			// Conatiner to store all the Colliding edge data
			std::vector<ColliderEdge> m_edgelist;

			// All the face normals used for detection
			std::vector<Vector3> m_normallist;

		};
	}
}

