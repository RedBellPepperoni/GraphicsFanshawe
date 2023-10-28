#pragma once
#include "Engine/Utils/Math.h"

namespace FanshaweGameEngine
{
	
		class Light
		{


		public:

			Light() {};
			virtual ~Light() {};

			void SetColor(const Vector3 color);
			void SetIntensity(const float newIntensity);
			void SetSpecular(const float newSpec);



			const Vector3 GetColor() const;
			const float GetIntenstity() const;
			const float GetSpecular() const;


		private:


			
			float m_intensity = 0.7f;
			float m_specular = 0.5f;

			Vector3 m_color = Vector3(1.0f);

		};
	
}

