#pragma once
#include "Light.h"
#include "Engine/Utils/Math.h"


namespace FanshaweGameEngine
{
	
		class DirectionLight : public Light
		{
			// Nothing to Do here
		public:

			DirectionLight() {};
			~DirectionLight() {};
		

			void SetDirection(Vector3& newDirection);
			const Vector3 GetDirection() const;

		private:

			Vector3 m_direction = Vector3(1.0f,1.0f,1.0f);

		};
	
}

