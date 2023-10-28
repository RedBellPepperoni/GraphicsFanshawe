#include "PointLight.h"

namespace FanshaweGameEngine
{
		const float PointLight::GetRadius() const
		{
			return m_radius;
		}

		void PointLight::SetRadius(const float newRadius)
		{
			if (newRadius < 0.0f)
			{
				m_radius = 0.0f;
			}
			else
			{
				m_radius = newRadius;
			}
		}
	
}