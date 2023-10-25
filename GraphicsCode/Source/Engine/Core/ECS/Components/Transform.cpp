#include "Transform.h"

namespace FanshaweGameEngine
{
	namespace Components
	{


		Transform::Transform()
			: m_position(Vector3(0.0f))
			, m_rotation(Quaternion(1.0f, 1.0f, 1.0f, 1.0f))
			, m_scale(Vector3(1.0f))
			, m_localMatrix(Matrix4(1.0f))
		{
			UpdateMatrix(m_localMatrix);
		}
		Transform::~Transform()
		{
		}
		const Vector3 Transform::GetPosition() const
		{
			return m_position;
		}
		const Quaternion Transform::GetRotation() const
		{
			return m_rotation;
		}
		const Vector3 Transform::GetEulerRotation() const
		{
			return GetEularAngles(m_rotation);
		}

		void Transform::UpdateMatrix(Matrix4& mat) const
		{
			Matrix4 matModel = Matrix4(1.0f);

			// translating the model
			matModel = Math::Translate(matModel, m_position);

			//matModel = Math::Rotate(matModel,)

			// scaling teh model
			matModel = Math::Scale(matModel, m_scale);

			mat = matModel;
		}

		Matrix4 Transform::GetLocalMatrix()
		{
			UpdateMatrix(m_localMatrix);
			return m_localMatrix;
		}

		const Vector3 Transform::GetScale() const
		{
			return m_scale;
		}


		void Transform::SetPosition(const Vector3& newPosition)
		{
			m_position = newPosition;
		}

		void Transform::SetRotation(const Quaternion& newRot)
		{
			m_rotation = newRot;
		}

		

		Vector3 Transform::GetUpVector()
		{
			Vector3 newUp = Vector3(0.0f, 1.0f, 0.0f);

			newUp = Math::GetQuaternion(m_localMatrix) * newUp;

			return newUp;
		}

		Vector3 Transform::GetRightVector()
		{
			Vector3 newRight = Vector3(1.0f, 0.0f, 0.0f);

			newRight = Math::GetQuaternion(m_localMatrix) * newRight;

			return newRight;
		}

		Vector3 Transform::GetForwardVector()
		{
			Vector3 newForward = Vector3(0.0f, 0.0f, 1.0f);

			newForward = Math::GetQuaternion(m_localMatrix) * newForward;

			return newForward;
		}

	}
}