#pragma once
#include "Engine/Utils/Math.h"
#include <string>

namespace FanshaweGameEngine
{
	enum class LightType : uint8_t
	{
		DirectionLight = 0,
		SpotLight = 1,
		PointLight = 2
	};

	
	struct Light
	{

		static std::string GetStringfromType(const LightType& type);

		Vector3 color = Vector3(1.0f);
		Vector3 position = Vector3(0.0f);
		Vector3 direction = Vector3(0.0f);

		float intensity = 10.0f;
		float radius = 0.0f;
		LightType type = LightType::PointLight;
		float innerAngle = 0.0f;
		float outerAngle = 0.0f;


	};
	
}

