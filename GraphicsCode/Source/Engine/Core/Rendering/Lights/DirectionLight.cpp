#include "DirectionLight.h"

namespace FanshaweGameEngine
{
		void DirectionLight::SetDirection(Vector3& newDirection)
		{
			m_direction = newDirection;

		}
		const Vector3 DirectionLight::GetDirection() const
		{
			return m_direction;
		}
	
}