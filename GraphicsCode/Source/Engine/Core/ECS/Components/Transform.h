#pragma once
#include "Engine/Utils/Math.h"

namespace FanshaweGameEngine
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

		// The parent/World Matric for the Transform
		Matrix4 m_worldTransform;

		

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

		const Vector3 GetScale() const;

		// ================= SETTERS ========================

		void SetWorldMatrix(const Matrix4& parentMatrix);

		void SetPosition(const Vector3& newPosition);


	};
}