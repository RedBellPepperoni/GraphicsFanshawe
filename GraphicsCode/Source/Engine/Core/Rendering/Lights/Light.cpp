#include "Light.h"

namespace FanshaweGameEngine
{
	namespace Rendering
	{
		void Light::SetColor(const Vector3 color)
		{
			m_color = color;
		}
		void Light::SetAmbientIntensity(const float newAmbIntensity)
		{
			m_ambientIntentisy = Clamp(newAmbIntensity, 0.0f, 1.0f);

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
		const Vector3 Light::GetColor() const
		{
			return m_color;
		}
		const float Light::GetAmbientIntensity() const
		{
			return m_ambientIntentisy;
		}
		const float Light::GetIntenstity() const
		{
			return m_intensity;
		}
	}
}