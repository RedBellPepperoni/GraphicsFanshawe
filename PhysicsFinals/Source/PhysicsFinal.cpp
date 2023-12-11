#pragma once
#include "GameEngine.h"
#include "Engine/Utils/Math/Random.h"

using namespace FanshaweGameEngine::Physics;

class PhysicsFinals : public Application
{


   


    void OnInit()
    {
        GetModelLibrary()->LoadModel("StarDestroyer", "Assets\\Models\\StarDestroyer.fbx");
        //GetTextureLibrary()->LoadTexture("Grey", )


        AddDirLight(Vector3(0.0f, 0.0f, 0.0f), Vector3(-20.0f, 10.0f, 0.0f), Vector3(1.0f, 1.0f, 0.85f), 1.0f);
        CreateStarDestroyer();

    }


    void OnUpdate(float deltaTime)
    {

    }





    void CreateStarDestroyer()
    {
        Entity starDestroyerEntity = GetCurrentScene()->CreateEntity("StarDestroyer");


        SharedPtr<Mesh> stardestoyerMesh = GetModelLibrary()->GetResource("StarDestroyer")->GetMeshes()[0];

        starDestroyerEntity.AddComponent<MeshComponent>(stardestoyerMesh);

        SharedPtr<Material> material = starDestroyerEntity.AddComponent<MeshRenderer>().GetMaterial();
        material->textureMaps.albedoMap = GetTextureLibrary()->GetResource("DefaultAlbedoTexture");
        material->metallic = 0.5f;
       // SharedPtr<BoxCollider> collider = Factory<BoxCollider>::Create();
       // collider->SetHalfDimensions(Vector3(0.57f, 0.2f, 0.57f)); 
       // 
       ///* SharedPtr<MeshCollider> collider = Factory<MeshCollider>::Create();
       // collider->BuildFromMesh(stardestoyerMesh.get());*/

       // PhysicsProperties properties;

       // properties.collider = collider;
       // properties.isStatic = false;
       // properties.stationary = false;
       // properties.mass = 10.0f;
       // properties.position = Vector3(0.0f);
       // properties.rotation = Quaternion(Radians(Vector3(0.0f, 0.0f, 0.0f)));
       // properties.elasticity = 0.6f;
       // properties.friction = 0.5f;
       // properties.velocity = Vector3(0.0f);

       // RigidBody3D* body = GetPhysicsEngine()->CreateRigidBody(starDestroyerEntity, properties);


        //Transform& transform = starDestroyerEntity.AddComponent<Transform>();

        //transform.SetPosition(Vector3(0.0f));
        //transform.SetRotation(Quaternion(Radians(Vector3(0.0f))));
        //transform.SetScale(Vector3(0.5f));


    }


    void AddDirLight(const Vector3& position, const Vector3& rotation, const Vector3& color, const float intensity)
    {
        Entity dirLight = m_currentScene->CreateEntity("DirectionalLight");

        Transform& transform = dirLight.AddComponent<Transform>();
        transform.SetPosition(position);
        transform.SetRotation(Quaternion(Radians(rotation)));

        Light& light = dirLight.AddComponent<Light>();
        light.type = LightType::DirectionLight;
        light.color = color;
        light.intensity = intensity <= 0.0f ? 0.0f : intensity;
        light.direction = Normalize(transform.GetForwardVector());
    }







};


int main(int argc, char* argv)
{
    // Creating a new Appinstance
    PhysicsFinals* app = new PhysicsFinals();

    //FilePath path = File::GetCurrentPath();

    // Always Initialize the App
    app->Initialize();
    // Running the Application
    app->Run();


    delete app;
}