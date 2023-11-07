#pragma once
#include "nlohmann/json.hpp"
#include "Source/Engine/Core/Scene/Scene.h"

namespace FanshaweGameEngine
{

	class SceneSerializer
	{;
	SceneSerializer() {};
	~SceneSerializer() {};



		// A temporary fix before i use c++ reflection 
	void SerializeEntities(Scene* scene);

	void DeserializeEntities(const std::string filePath);

	};

}

