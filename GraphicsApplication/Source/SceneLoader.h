#pragma once
#include "GameEngine.h"


class SceneLoader
{
public:
	SceneLoader();
	~SceneLoader() = default;


	void LoadModel(const std::string& name, const std::string& modelpath);

	void SpawnObject(const std::string& meshName, const Vector3& position, const Vector3& rotation, const Vector3& scale);


private:

	SharedPtr<ModelLibrary> modelLibrary = nullptr;
	Scene* sceneRef = nullptr;

	int entityCount = 0;

};

