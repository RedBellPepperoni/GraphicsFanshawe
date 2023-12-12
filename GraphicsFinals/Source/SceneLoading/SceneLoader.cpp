#include "SceneLoader.h"
#include "SceneParser.h"
#include "GameEngine.h"

using namespace FanshaweGameEngine;
using namespace FanshaweGameEngine::Physics;

SceneLoader::SceneLoader()
{
	modelLibrary = Application::GetCurrent().GetModelLibrary();
	textureLibrary = Application::GetCurrent().GetTextureLibrary();

	sceneRef = Application::GetCurrent().GetCurrentScene();

}

void SceneLoader::LoadModel(const std::string& name, const std::string& modelpath)
{
	modelLibrary->LoadModel(name, modelpath);
}

void SceneLoader::LoadTexture(const std::string& name, const std::string& path)
{
	textureLibrary->LoadTexture(name, path, TextureFormat::RGBA);
}



void SceneLoader::SpawnObject(const ObjectData& data)
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

	transform->SetPosition(data.position);
	transform->SetEularRotation(data.rotation);
	transform->SetScale(data.scale);
	//transform->SetScale(Vector3(1.0f,1.0f,1.0f));


	//PhysicsProperties
	

	SharedPtr<Mesh> mesh = modelLibrary->GetResource(data.meshName)->GetMeshes()[0];
	//SharedPtr<Mesh> mesh = modelLibrary->GetResource("Ground")->GetMeshes()[0];

	entity.AddComponent<MeshComponent>(mesh);
	SharedPtr<Material> material = entity.AddComponent<MeshRenderer>().GetMaterial();

	material->textureMaps.albedoMap = textureLibrary->GetResource(data.albedoTexture);
	material->metallic = data.metallic;
	material->type = MaterialType::Opaque;
	
}

