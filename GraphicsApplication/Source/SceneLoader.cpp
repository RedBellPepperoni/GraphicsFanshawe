#include "SceneLoader.h"

using namespace FanshaweGameEngine;

SceneLoader::SceneLoader()
{
	modelLibrary = Application::GetCurrent().GetModelLibrary();

	sceneRef = Application::GetCurrent().GetCurrentScene();

}

void SceneLoader::LoadModel(const std::string& name, const std::string& modelpath)
{
	modelLibrary->LoadModel(name, modelpath);
}

void SceneLoader::SpawnObject(const std::string& meshName, const Vector3& position, const Vector3& rotation, const Vector3& scale)
{
	if (!sceneRef)
	{
		LOG_WARN("Scene Reference Empty");
		return;
	}

	if (!modelLibrary)
	{
		LOG_WARN("ModelLibrary Reference Empty");
		return;
	}

	std::string name = "Entity_" + std::to_string(entityCount);

	Entity entity = sceneRef->CreateEntity(name);

	Transform* transform = &entity.AddComponent<Transform>();

	transform->SetPosition(position);
	transform->SetRotation(rotation);
	transform->SetScale(scale);

	modelLibrary;

	SharedPtr<Mesh> mesh = modelLibrary->GetResource(meshName)->GetMeshes()[0];
	//SharedPtr<Mesh> mesh = modelLibrary->GetResource("Ground")->GetMeshes()[0];

	entity.AddComponent<MeshComponent>(mesh);
	entity.AddComponent<MeshRenderer>();



	
}

