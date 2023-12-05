
#pragma once
#include "GameEngine.h"

using namespace FanshaweGameEngine::Physics;

class PhysicsProject : public Application
{
   

    void OnInit()
    {
        GetModelLibrary()->LoadModel("PhysicsBase","Assets\\Models\\PhysicsBase.fbx");
        GetModelLibrary()->LoadModel("Sphere","Assets\\Models\\Sphere.fbx");

       

        GetPhysicsEngine()->SetGravity(Vector3(0.0f, - 9.81f, 0.0f));
        GetPhysicsEngine()->SetPaused(true);
       
        CreateBase();


        AddDirLight(Vector3(0.0f, 0.0f, 0.0f), Vector3(-60.0f, 20.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), 0.8f);


        CreateCapsule(Vector3(0.0f, 10.0f, 0.0f), 4.0f, 5.0f);

        CreateSphere(Vector3(0.5f,  30.0f, 0.5f), 1.0f);
        CreateSphere(Vector3(0.3f,  35.0f, 0.3f), 1.0f);
        CreateSphere(Vector3(-0.5f,  40.0f, -0.3f), 1.0f);

        //for (int i = -50; i < 50; i += 10)
        //{
        //    for (int j = -50; j < 50; j += 10)
        //    {
        //        CreateCapsule(Vector3(i,  10.0f, j), 4.0f,5.0f);

        //        CreateSphere(Vector3(i,  30.0f, j), 3.0f);
        //       /* CreateSphere(Vector3(i, (i + j) / 2 + 150.0f, j), 1.0f);
        //        CreateSphere(Vector3(i, (i + j) / 2 + 180.0f, j), 1.0f);
        //        CreateSphere(Vector3(i, (i + j) / 2 + 210.0f, j), 1.0f);
        //        CreateSphere(Vector3(i, (i + j) / 2 + 240.0f, j), 1.0f);
        //        CreateSphere(Vector3(i, (i + j) / 2 + 270.0f, j), 1.0f);*/
        //    }
        //}


    }

    void OnUpdate(float deltaTime)
    {
        if (Input::InputSystem::GetInstance().GetKeyDown(Input::Key::G))
        {
            GetPhysicsEngine()->SetPaused(!GetPhysicsEngine()->GetIsPaused());

            //GetCurrent().
        }

       
        
    }

    void CreateBase()
    {
        Entity physicBase = GetCurrentScene()->CreateEntity("PhysicsBase");


        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("PhysicsBase")->GetMeshes()[0];

        //physicBase.AddComponent<MeshComponent>(mesh);
        //physicBase.AddComponent<MeshRenderer>();


        //SharedPtr<MeshCollider> collider = Factory<MeshCollider>::Create();
       // collider->BuildFromMesh(mesh.get());
        SharedPtr<BoxCollider> collider = Factory<BoxCollider>::Create(Vector3(50.0f, 3.0f, 50.0f));
       
        PhysicsProperties properties;

        properties.collider = collider;
        properties.isStatic = true;
        properties.stationary = true;
        properties.position = Vector3(0.0f, -13.0f,0.0f);
        properties.mass = 1000.0f;
        properties.elasticity = 0.6f;
        properties.friction = 3.0f;
        //properties.rotation = Quaternion(Radians(Vector3(30.0f,0.0f,0.0f)));

        GetPhysicsEngine()->CreateRigidBody(physicBase,properties);
        
      

        
    }

    void CreateCapsule(const Vector3& position, const float radius,const float height)
    {
        Entity ballObject = GetCurrentScene()->CreateEntity("PhysicsBase");
        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("Sphere")->GetMeshes()[0];

        ballObject.AddComponent<MeshComponent>(mesh);
        ballObject.AddComponent<MeshRenderer>();


       // SharedPtr<SphereCollider> collider = Factory<SphereCollider>::Create();
        SharedPtr<CapsuleCollider> collider = Factory<CapsuleCollider>::Create();
        collider->SetRadius(radius);
        collider->SetHeight(height);
    
        PhysicsProperties properties;

        properties.collider = collider;
        properties.isStatic = false;
        properties.stationary = false;
        properties.mass = 50.0f;
        properties.position = position;
        properties.elasticity = 0.6f;
        properties.friction = 2.0f;

        Physics::RigidBody3D* rigidBody = GetPhysicsEngine()->CreateRigidBody(ballObject, properties);




    }

    void CreateSphere(const Vector3& position, const float radius)
    {
        Entity ballObject = GetCurrentScene()->CreateEntity("Sphere");
        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("Sphere")->GetMeshes()[0];

        ballObject.AddComponent<MeshComponent>(mesh);
        ballObject.AddComponent<MeshRenderer>();


        SharedPtr<SphereCollider> collider = Factory<SphereCollider>::Create();
        collider->SetRadius(radius);
        

        PhysicsProperties properties;

        properties.collider = collider;
        properties.isStatic = false;
        properties.stationary = false;
        properties.mass = 10.0f;
        properties.position = position;
        properties.elasticity = 0.6f;
        properties.friction = 3.0f;

        Physics::RigidBody3D* rigidBody = GetPhysicsEngine()->CreateRigidBody(ballObject, properties);




    }

    void AddDirLight(const Vector3& position, const Vector3& rotation, const Vector3& color, const float intensity)
    {
        Entity dirLight = m_currentScene->CreateEntity("DirectionalLight");

        Transform& transform = dirLight.AddComponent<Transform>();
        transform.SetPosition(position);
        transform.SetRotation(rotation);

        Light& light = dirLight.AddComponent<Light>();
        light.type = LightType::DirectionLight;
        light.color = color;
        light.intensity = intensity <= 0.0f ? 0.0f : intensity;

    }

};



int main(int argc, char* argv)
{
    // Creating a new Appinstance
    PhysicsProject* app = new PhysicsProject();

    //FilePath path = File::GetCurrentPath();

    // Always Initialize the App
    app->Initialize();
    // Running the Application
    app->Run();


    delete app;
}