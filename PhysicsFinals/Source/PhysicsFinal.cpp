#pragma once
#include "GameEngine.h"
#include "Engine/Utils/Math/Random.h"
#include "XwingDirector.h"

using namespace FanshaweGameEngine::Physics;


class PhysicsFinals : public Application
{


   


    void OnInit()
    {
        //GetModelLibrary()->LoadModel("StarDestroyer", "Assets\\Models\\StarDestroyer.fbx");
        //GetTextureLibrary()->LoadTexture("Grey", )
        Application::GetCurrent().GetModelLibrary()->LoadModel("StarDestroyerc", "Assets\\Models\\ShipGenMesh.fbx");
        Application::GetCurrent().GetModelLibrary()->LoadModel("XWing", "Assets\\Models\\Xwing.fbx");
        Application::GetCurrent().GetModelLibrary()->LoadModel("Sphere", "Assets\\Models\\Sphere.fbx");
        Application::GetCurrent().GetTextureLibrary()->LoadTexture("XWingAlbedo", "Assets\\Textures\\xwing.jpg", TextureFormat::RGB);

        AddDirLight(Vector3(0.0f, 0.0f, 0.0f), Vector3(-20.0f, 10.0f, 0.0f), Vector3(1.0f, 1.0f, 0.85f), 1.0f);


        CreateStarDestroyer();

        XwingDirector::GetInstance().SpawnTestSpherePair();
        XwingDirector::GetInstance().SetCameraController();

        for (int i = 0; i < 1; i++)
        {
            XwingDirector::GetInstance().SpawnXWing();
        }
       
       // XwingDirector::GetInstance().SpawnXWing();

       // XwingDirector::GetInstance().TempStartAll();

      



    }


    void OnUpdate(float deltaTime)
    {
        if(Input::InputSystem::GetInstance().GetKeyDown(Input::Key::G))
        {
            XwingDirector::GetInstance().TempStartAll();
        }


        XwingDirector::GetInstance().Update(deltaTime);
    }





    void CreateStarDestroyer()
    {
        Entity starDestroyerEntity = GetCurrentScene()->CreateEntity("StarDestroyer");


       // SharedPtr<Mesh> stardestoyerMesh = GetModelLibrary()->GetResource("StarDestroyer")->GetMeshes()[0];
       // 
       // starDestroyerEntity.AddComponent<MeshComponent>(stardestoyerMesh);

       // SharedPtr<Material> material = starDestroyerEntity.AddComponent<MeshRenderer>().GetMaterial();
       // material->textureMaps.albedoMap = GetTextureLibrary()->GetResource("DefaultAlbedoTexture");
       // material->metallic = 0.5f;
       ////
        SharedPtr<Mesh> scolMesh = GetModelLibrary()->GetResource("StarDestroyerc")->GetMeshes()[0];
        SharedPtr<MeshCollider> collider = Factory<MeshCollider>::Create();
        collider->BuildFromMesh(scolMesh.get());

        //SharedPtr<BoxCollider> collider = Factory<BoxCollider>::Create();
        ////collider->SetHalfDimensions(Vector3(300.0f, 20.0f, 500.0f)); 
        //collider->SetHalfDimensions(Vector3(100.0f, 100.0f, 100.0f)); 

        PhysicsProperties properties;

        properties.collider = collider;
        properties.isStatic = false;
        properties.stationary = true;
        properties.mass = 1000.0f;
        properties.position = Vector3(0.0f);
        properties.rotation = Quaternion(Radians(Vector3(0.0f, 0.0f, 0.0f)));
        properties.elasticity = 0.6f;
        properties.friction = 0.5f;
        properties.velocity = Vector3(0.0f);
        properties.tag = CollisionTag::StarDestroyer;

        RigidBody3D* body = GetPhysicsEngine()->CreateRigidBody(starDestroyerEntity, properties);

        body->m_OnCollisionCallback = std::bind(&PhysicsFinals::OnCollision, this, std::placeholders::_1, std::placeholders::_2);
  

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


    bool OnCollision(RigidBody3D* body, Vector3 collisionpoint)
    {

        if (body->m_tag == CollisionTag::TestSphere)
        {
            LOG_CRITICAL("Spherecheck Failed");
        }
        else if (body->m_tag == CollisionTag::Xwing)
        {
            LOG_CRITICAL("XWing Crashed _ This shouldnt happen");
        }
        
        return false;
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