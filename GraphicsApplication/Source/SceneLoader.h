#pragma once
#include "GameEngine.h"


struct ObjectData;

class SceneLoader
{
public:
	SceneLoader();
	~SceneLoader() = default;


	void LoadModel(const std::string& name, const std::string& modelpath);

	void SpawnObject(const ObjectData& data);


private:

	SharedPtr<ModelLibrary> modelLibrary = nullptr;
	SharedPtr<TextureLibrary> textureLibrary = nullptr;

	Scene* sceneRef = nullptr;

	int entityCount = 0;

};

