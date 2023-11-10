#pragma once
#include "GameEngine.h"

using namespace FanshaweGameEngine::Physics;

class SceneLoader
{
public:
	SceneLoader();
	~SceneLoader() = default;


	void LoadModel(const std::string& name, const std::string& modelpath);

	void SpawnRenderObject(const std::string& meshName, const Vector3& position, const Vector3& rotation, const Vector3& scale);
	void SpawnMarbles(const Vector3& position);
   
	void SpawnPhysicsSpace();

private:

	SharedPtr<ModelLibrary> modelLibrary = nullptr;
	Scene* sceneRef = nullptr;

	int entityCount = 0;

};

