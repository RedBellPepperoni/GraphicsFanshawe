#pragma once
#include "Engine/Utils/Math.h"

namespace FanshaweGameEngine
{
	namespace Rendering
	{

		class Light
		{

		public:

			void SetColor(const Vector3 color);
			void SetAmbientIntensity(const float newAmbIntensity);
			void SetIntensity(const float newIntensity);



			const Vector3 GetColor() const;
			const float GetAmbientIntensity() const;
			const float GetIntenstity() const;
			


		private:


			float m_ambientIntentisy = 0.2f;
			float m_intensity = 0.7f;

			Vector3 m_color = Vector3(1.0f);

		};
	}
}

