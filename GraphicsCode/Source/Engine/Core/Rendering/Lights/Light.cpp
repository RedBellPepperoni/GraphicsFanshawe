#include "Light.h"

namespace FanshaweGameEngine
{
	
		std::string Light::GetStringfromType(const LightType& type)
		{
			switch (type)
			{
			case FanshaweGameEngine::LightType::DirectionLight: 
				return "Directional";
				
			case FanshaweGameEngine::LightType::SpotLight:
				return "Spot";

			case FanshaweGameEngine::LightType::PointLight:
				return "Point";

			default:
				return "UndefinedType";
			}
		}

}