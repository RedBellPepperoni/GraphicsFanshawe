#include "Skybox.h"



namespace FanshaweGameEngine
{
	namespace Rendering
	{
		void Skybox::SetIntensity(float intensity)
		{
			m_intensity = intensity;
		}

		const float Skybox::GetIntensity() const
		{
			return m_intensity;
		}
		Quaternion Skybox::GetRotaionQuat() const
		{
			Vector3 radianVec = Vector3(Radians(m_rotation.x), Radians(m_rotation.y), Radians(m_rotation.z));

			return Quaternion(MakeRotationMatrix(radianVec));
		
		}

		void Skybox::SetRotation(const Quaternion& quat)
		{
			Vector3 degreeVector = GetEularAngles(quat);
			degreeVector.x = Degrees(degreeVector.x);
			degreeVector.y = Degrees(degreeVector.y);
			degreeVector.z = Degrees(degreeVector.z);

			SetRotation(degreeVector);
		}
		void Skybox::RotateX(float angle)
		{
			Rotate(Vector3(angle, 0.0f, 0.0f));
		}
		void Skybox::RotateY(float angle)
		{
			Rotate(Vector3(0.0f, angle, 0.0f));
		}
		void Skybox::RotateZ(float angle)
		{
			Rotate(Vector3(0.0f, 0.0f, angle));
		}
		void Skybox::Rotate(const Vector3& angles)
		{
			m_rotation += angles;
			m_rotation.x = std::fmod(m_rotation.x, 360.0f);
			m_rotation.y = std::fmod(m_rotation.y, 360.0f);
			m_rotation.z = std::fmod(m_rotation.z, 360.0f);

		}
		const Vector3& Skybox::GetRotation() const
		{
			return m_rotation;
		}

		void Skybox::SetRotation(const Vector3& angles)
		{
			m_rotation = Vector3(0.0f);
			Rotate(angles);
		}

	}
}