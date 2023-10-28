#pragma once
#include "Light.h"


namespace FanshaweGameEngine
{
		class PointLight : public Light
		{


		public:


			PointLight() {};
			~PointLight() {};

			const float GetRadius() const;

			void SetRadius(const float newRadius);

		private:

			float m_radius = 1.0f;

		};

}

