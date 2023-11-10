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





void SceneLoader::SpawnRenderObject(const std::string& meshName, const Vector3& position, const Vector3& rotation, const Vector3& scale)
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

void SceneLoader::SpawnMarbles(const Vector3& position)
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

	std::string name = "Marble";

	Entity entity = sceneRef->CreateEntity(name);


	SharedPtr<Mesh> mesh = modelLibrary->GetResource("Marble")->GetMeshes()[0];

	entity.AddComponent<MeshComponent>(mesh);
	entity.AddComponent<MeshRenderer>();


	PhysicsProperties marbleProperties;

	SharedPtr<SphereCollider> collider = Factory<SphereCollider>::Create();

	collider->SetRadius(1.0f);

	marbleProperties.collider = collider;
	marbleProperties.position = position;

	marbleProperties.mass = 1.0f;
	marbleProperties.isStatic = false;
	marbleProperties.friction = 0.8f;
	

	Application::GetCurrent().GetPhysicsEngine()->CreateRigidBody(entity, marbleProperties);

	

	
	
}


void SceneLoader::SpawnPhysicsSpace()
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

	std::string name = "Base";

	Entity entity = sceneRef->CreateEntity(name);




	SharedPtr<Mesh> mesh = modelLibrary->GetResource("Base")->GetMeshes()[0];

	entity.AddComponent<MeshComponent>(mesh);
	entity.AddComponent<MeshRenderer>();


	PhysicsProperties baseproperty;

	SharedPtr<MeshCollider> collider = Factory<MeshCollider>::Create();
	collider->BuildFromMesh(mesh.get());


	

	//SharedPtr<BoxCollider> collider = Factory<BoxCollider>::Create();

	//
	// 
	// baseproperty.rotation = Quaternion(Vector3(Radians(10.0f), 0.0f, 0.0f));

	baseproperty.collider = collider;
	baseproperty.mass = 100.0f;
	baseproperty.friction = 0.9f;
	baseproperty.isStatic = true;


    Application::GetCurrent().GetPhysicsEngine()->CreateRigidBody(entity, baseproperty);

	//body->SetStatic(true);



	name = "Ramp";

	entity = sceneRef->CreateEntity(name);




	mesh = modelLibrary->GetResource("Ramp")->GetMeshes()[0];

	entity.AddComponent<MeshComponent>(mesh);
	entity.AddComponent<MeshRenderer>();


	PhysicsProperties rampProperty;

	collider = Factory<MeshCollider>::Create();
	collider->BuildFromMesh(mesh.get());


	rampProperty.collider = collider;
	rampProperty.isStatic = false;
	rampProperty.mass = 100.0f;
	rampProperty.friction = 0.9f;
	rampProperty.position = Vector3(0.0f, 1.0f, 0.0f);



	RigidBody3D* body = Application::GetCurrent().GetPhysicsEngine()->CreateRigidBody(entity, rampProperty);

	body->m_isStatic = true;


	


}

