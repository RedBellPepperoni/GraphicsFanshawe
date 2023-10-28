#include "Light.h"

namespace FanshaweGameEngine
{
	
		void Light::SetColor(const Vector3 color)
		{
			m_color = color;
		}
		
		void Light::SetIntensity(const float newIntensity)
		{
			if (newIntensity < 0.0f)
			{
				m_intensity = 0.0f;
			}
			else
			{
				m_intensity = newIntensity;
			}
		}

		void Light::SetSpecular(const float newSpec)
		{
			if (newSpec < 0.0f)
			{
				m_specular = 0.0f;
			}
			else
			{
				m_specular = newSpec;
			}
		}


		const Vector3 Light::GetColor() const
		{
			return m_color;
		}
		
		const float Light::GetIntenstity() const
		{
			return m_intensity;
		}
		const float Light::GetSpecular() const
		{
			return 0.0f;
		}
	
}