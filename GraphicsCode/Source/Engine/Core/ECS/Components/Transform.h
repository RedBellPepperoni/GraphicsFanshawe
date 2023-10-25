#pragma once
#include "Engine/Utils/Math.h"

namespace FanshaweGameEngine
{
	
	namespace Components
	{


		class Transform
		{

		protected:

			

			// The local position of the Transform
			Vector3 m_position;

			//The local Rotation in Quaternion to overcome "Gimble Lock"
			Quaternion m_rotation;

			// The Local Scale of the transform
			Vector3 m_scale;

			// The local Matric for the Transform
			Matrix4 m_localMatrix = Matrix4(1.0f);

			void UpdateMatrix(Matrix4& mat) const;

		public:

			


			Transform();
			~Transform();

			// ================ GETTERS ========================

			// Get the world Position of the object
			const Vector3 GetPosition() const;

			// Get the world Rotation of the Object in Quaternion
			const Quaternion GetRotation() const;

			// Get the world Rotation in Euler angles
			const Vector3 GetEulerRotation() const;



			Matrix4 GetLocalMatrix();

			const Vector3 GetScale() const;

			// ================= SETTERS ========================


			void SetPosition(const Vector3& newPosition);

			void SetRotation(const Quaternion& newRot);

			

			Vector3 GetUpVector();

			Vector3 GetRightVector();

			Vector3 GetForwardVector();

		};
	}
}