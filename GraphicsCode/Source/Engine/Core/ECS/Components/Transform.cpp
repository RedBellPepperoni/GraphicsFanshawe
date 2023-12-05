#include "Transform.h"

namespace FanshaweGameEngine
{
	namespace Components
	{


		Transform::Transform()
			: m_position(Vector3(0.0f))
			, m_rotation(Quaternion())
			, m_scale(Vector3(1.0f))
			, m_worldMatrix(Matrix4(1.0f))
		{
			UpdateMatrix(m_worldMatrix);
		}
		Transform::~Transform()
		{
		}
		const Vector3& Transform::GetPosition() const
		{
			return m_position;
		}
		const Quaternion& Transform::GetRotation() const
		{
			return m_rotation;
		}
		const Vector3 Transform::GetEulerRotation() const
		{
			Vector3 rot = GetEularAngles(m_rotation);

			Vector3 degreerot = Vector3(Degrees(rot.x), Degrees(rot.y), Degrees(rot.z));

			return degreerot;
		}

		void Transform::UpdateMatrix(Matrix4& mat) const
		{
			Matrix4 matModel = Matrix4(1.0f);

			mat = Math::Translate(matModel, m_position) * Math::QuatToMatrix(m_rotation) *  Math::Scale(matModel, m_scale);

		}

	    Matrix4 Transform::GetLocalMatrix()
		{
			Matrix4 mat;
			UpdateMatrix(mat);
			return mat;
		}

		Matrix4& Transform::GetNormalMatrix()
		{
			// Just incase
			UpdateMatrix(m_worldMatrix);
				
			m_normalMatrix =  Transpose(Inverse(m_worldMatrix));

			return m_normalMatrix;

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

		void Transform::SetRotation(const Vector3& eularRot)
		{

			m_rotation = Quaternion(Vector3(Radians(eularRot.x), Radians(eularRot.y), Radians(eularRot.z)));
		}

		

		void Transform::SetScale(const Vector3& newScale)
		{
			m_scale = newScale;
		}
		

		Vector3 Transform::GetUpVector()
		{
			Vector3 newUp = Vector3(0.0f, 1.0f, 0.0f);

			return (GetRotation() * newUp);
		}

		Vector3 Transform::GetRightVector()
		{
			Vector3 newRight = Vector3(1.0f, 0.0f, 0.0f);

			return (GetRotation()* newRight);
		}

		Vector3 Transform::GetForwardVector()
		{
			// Open GL is stupid and has -z as forward
			Vector3 newForward = Vector3(0.0f, 0.0f, -1.0f);

			return (GetRotation() * newForward);
		}

	}
}