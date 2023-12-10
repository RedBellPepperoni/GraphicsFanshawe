
#pragma once
#include "SceneParser.h"
#include "SceneLoader.h"
#include "GameEngine.h"
#include "Engine/Utils/Math/Random.h"
#include "Engine/Core/System/Input/PlayerController.h"
#include "Engine/Core/Rendering/Essentials/Camera.h"

using namespace FanshaweGameEngine::Physics;



class PhysicsProject : public Application
{
   

    void OnInit()
    {
        parser = Factory<SceneParser>::Create();
        loader = Factory<SceneLoader>::Create();

        // parse the scene with the name
        parser->ParseScene("Engine\\Scene\\ScenePhysics.json");

        // Retrives the parsed models
        std::map<std::string, std::string> modelmap = parser->GetModelList();

        std::map<std::string, std::string> texturMap = parser->GetTextureList();

        // Retrives the parsed object data
        std::vector<ObjectData> objectmap = parser->GetObjectList();


        // Load all the models from the model data list
        for (auto const& data : modelmap)
        {
            loader->LoadModel(data.first, data.second);
        }

        for (auto const& texture : texturMap)
        {
            loader->LoadTexture(texture.first, texture.second);
        }

        // Create objects according to the scene data
        for (ObjectData object : objectmap)
        {
            loader->SpawnObject(object);
        }






        GetPhysicsEngine()->SetGravity(Vector3(0.0f, 0.0f, 0.0f));
;
       
        CreateBase();
        //CreateTree(Vector3(10.0f, 0.0f, 0.0f));

        //for (int i = -100; i < 100; i+=20)
        //{
        //    for (int j = -100; j < 100; j+=20)
        //    {
        //        CreateTree(Vector3((float)i, 0.0f, (float)j), Vector3(Random32::Range(-30,30),0.0f,Random32::Range(-20,20)));
        //    }
        //}


        CreatePlayer(Vector3(0.0f,50.0f,0.0f));
        CreateFollowCamera(Vector3(0.0f, 10.0f, 0.0f));
        AddDirLight(Vector3(0.0f, 0.0f, 0.0f), Vector3(-45.0f, -43.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), 3.0f);

   


        RestartGame();



    }

    void OnUpdate(float deltaTime)
    {
       
        Vector2 mousePosition = Input::InputSystem::GetInstance().GetMousePosition();
        ComponentView cameraView = GetCurrentScene()->GetEntityManager()->GetComponentsOfType<Camera>();
        ComponentView playerControllerView = GetCurrentScene()->GetEntityManager()->GetComponentsOfType<PlayerController>();




        if (!playerControllerView.IsEmpty() && !cameraView.IsEmpty())
        {
          

            PlayerController& controller = playerControllerView[0].GetComponent<PlayerController>();
            RigidBody3D& body = playerControllerView[0].GetComponent<RigidBody3D>();
            
            Camera& camera = cameraView[0].GetComponent<Camera>();
            Transform* transform = cameraView[0].TryGetComponent<Transform>();

            if (transform)
            {

                
                controller.KeyboardInput(body,*transform, deltaTime);
                controller.MouseInput(body,*transform, mousePosition, deltaTime);
                controller.UpdateOffsetTransform(body, *transform);

               
            
            }



        }


        if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::G))
        {
            RestartGame();
        }
        
    }

    void CreateBase()
    {
        Entity physicBase = GetCurrentScene()->CreateEntity("PhysicsBase");


        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("Ground")->GetMeshes()[0];

        physicBase.AddComponent<MeshComponent>(mesh);
        SharedPtr<Material> mat = physicBase.AddComponent<MeshRenderer>().GetMaterial();
        mat->textureMaps.albedoMap = GetTextureLibrary()->GetResource("GroundAlbedo");

       
        SharedPtr<BoxCollider> collider = Factory<BoxCollider>::Create(Vector3(80.0f, 0.2f, 80.0f));
       
        PhysicsProperties properties;

        properties.collider = collider;
        properties.isStatic = true;
        properties.stationary = true;
        properties.position = Vector3(-9.83f, 0.0f,0.0f);
        properties.mass = 1000.0f;
        properties.elasticity = 0.6f;
        properties.friction = 0.8f;
        //properties.rotation = Quaternion(Radians(Vector3(30.0f,0.0f,0.0f)));

        GetPhysicsEngine()->CreateRigidBody(physicBase,properties);
        
      

        
    }

    void CreateTree(const Vector3& position,const Vector3& rotation)
    {
        Entity ballObject = GetCurrentScene()->CreateEntity("PhysicsBase");
        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("ColliderTreeLeaves")->GetMeshes()[0];

        ballObject.AddComponent<MeshComponent>(mesh);
        ballObject.AddComponent<MeshRenderer>();

       /* SharedPtr<MeshCollider> collider = Factory<MeshCollider>::Create();
        collider->BuildFromMesh(mesh.get(), position);
       */
        SharedPtr<BoxCollider> collider = Factory<BoxCollider>::Create();
        collider->SetHalfDimensions(Vector3(1.0f, 7.0f, 1.0f));
        PhysicsProperties properties;

        properties.collider = collider;
        properties.isStatic = true;
        properties.stationary = true;
        properties.mass = 50.0f;
       // properties.position = position;
        properties.rotation = Quaternion(Radians(rotation));
        properties.position = position + Vector3(0.0f,7.0f,0.0f);
        properties.elasticity = 0.1f;
        properties.friction = 5.5f;

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
        properties.friction = 0.5f;

        Physics::RigidBody3D* rigidBody = GetPhysicsEngine()->CreateRigidBody(ballObject, properties);




    }

    void AddDirLight(const Vector3& position, const Vector3& rotation, const Vector3& color, const float intensity)
    {
        Entity dirLight = m_currentScene->CreateEntity("DirectionalLight");

        Transform& transform = dirLight.AddComponent<Transform>();
        transform.SetPosition(position);
        transform.SetEularRotation(rotation);

        Light& light = dirLight.AddComponent<Light>();
        light.type = LightType::DirectionLight;
        light.color = color;
        light.intensity = intensity <= 0.0f ? 0.0f : intensity;

    }

    void CreatePlayer(const Vector3& position)
    {
        Entity playerEntity = m_currentScene->CreateEntity("Player");
        
        PlayerController& controller = playerEntity.AddComponent<PlayerController>();
        controller.SetOffset(Vector3(0.0f,0.3f,-2.3f));

        SharedPtr<BoxCollider> collider = Factory<BoxCollider>::Create();
        collider->SetHalfDimensions(Vector3(0.57f,0.2f,0.57f));

        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("Drone")->GetMeshes()[0];
        playerEntity.AddComponent<MeshComponent>(mesh);
        SharedPtr<Material> mat = playerEntity.AddComponent<MeshRenderer>().GetMaterial();
        mat->textureMaps.albedoMap = GetTextureLibrary()->GetResource("DroneAlbedo");
        mat->metallic = 5.0f;

        PhysicsProperties properties;

        properties.collider = collider;
        properties.isStatic = false;
        properties.stationary = false;
        properties.mass = 10.0f;
        properties.position = position;
        properties.rotation = Quaternion(Radians(Vector3(0.0f, 0.0f, 0.0f)));
        properties.elasticity = 0.6f;
        properties.friction = 0.5f;
        properties.velocity = Vector3(0.0f);

        playerBody = GetPhysicsEngine()->CreateRigidBody(playerEntity, properties);

        controller.SetOnHit(playerBody);


        Entity Crack = m_currentScene->CreateEntity("CrackScreen");
        Transform* trans = &Crack.AddComponent<Transform>();

        SharedPtr<Mesh> crackmesh = GetModelLibrary()->GetResource("Crack")->GetMeshes()[0];
        Crack.AddComponent<MeshComponent>(crackmesh);

        SharedPtr<Material> crackmat = Crack.AddComponent<MeshRenderer>().GetMaterial();

        crackmat->textureMaps.albedoMap = GetTextureLibrary()->GetResource("CrackAlbedo");


        trans->SetPosition(Vector3(-10.0f));
        trans->SetRotation(Vector3(0.0f));
        trans->SetScale(Vector3(1.0f));

        controller.SetCrackReference(trans);

    }

    void CreateFollowCamera(const Vector3& position)
    {
        Entity cameraEntity = m_currentScene->CreateEntity("FollowCamera");
        Transform& transform = cameraEntity.AddComponent<Transform>();
        cameraEntity.AddComponent<Camera>();
        transform.SetPosition(position);


    }

    void RestartGame()
    {
        Vector3 startPosition = Vector3(-51.36, 5.0f, 15.00);
        //Vector3 startRotation = Vector3(0.0, 60.0f, 0.00);

        ComponentView playerControllerView = GetCurrentScene()->GetEntityManager()->GetComponentsOfType<PlayerController>();

        RigidBody3D& body = playerControllerView[0].GetComponent<RigidBody3D>();
        PlayerController& controller = playerControllerView[0].GetComponent<PlayerController>();



        body.SetPosition(startPosition);
        body.SetRotation(LookAtRotation(Normalize(Vector3(0.0f) - startPosition), Vector3(0.0f, 1.0f, 0.0f)));


        controller.Reset();

    }

    private:

        SharedPtr<SceneParser> parser = nullptr;
        SharedPtr<SceneLoader> loader = nullptr;

        RigidBody3D* playerBody = nullptr;

        
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