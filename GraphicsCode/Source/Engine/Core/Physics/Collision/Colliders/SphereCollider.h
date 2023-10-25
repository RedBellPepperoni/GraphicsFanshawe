#pragma once


//#pragma once
#include "Engine/Core/Physics/Collision/Colliders/Collider.h"

namespace FanshaweGameEngine
{
	namespace Physics
	{

		class SphereCollider : public Collider
		{
		public:

			SphereCollider();

			//May be add an explicit here later on if it clashes
			SphereCollider(float radius);


			~SphereCollider();


			virtual std::vector<Vector3>& GetCollisionNormals(const RigidBody3D* currentBody) override;

			virtual std::vector<ColliderEdge>& GetEdgeList(const RigidBody3D* currentBody) override;

			virtual void GetMinMaxFromAxis(const RigidBody3D* body, const Vector3& axis, Vector3* outMin, Vector3* outMax) override;


			void SetRadius(const float radius);

			const float GetRadius() const;

			float GetSize() const override;



		protected:

			// the radius of the Sphere Collider
			float m_radius;


		};



	}
}
