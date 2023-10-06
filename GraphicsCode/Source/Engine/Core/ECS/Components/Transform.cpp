#include "Transform.h"

namespace FanshaweGameEngine
{
	Transform::Transform()
		: m_position(Vector3(0.0f))
		, m_rotation(Quaternion(1.0f,1.0f,1.0f,1.0f))
		, m_scale(Vector3(1.0f))
		, m_worldTransform(Matrix4(1.0f))
	{
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
	
	const Vector3 Transform::GetScale() const
	{
		return m_scale;
	}

	void Transform::SetWorldMatrix(const Matrix4& parentMatrix)
	{
		// Do something here
	}
	void Transform::SetPosition(const Vector3& newPosition)
	{
		m_position = newPosition;
	}
}