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
        GetModelLibrary()->LoadModel("StarDestroyerFront", "Assets\\Models\\StarDestroyerFront.fbx");
        GetModelLibrary()->LoadModel("StarDestroyerMid", "Assets\\Models\\StarDestroyerMid.fbx");
        GetModelLibrary()->LoadModel("StarDestroyerBack", "Assets\\Models\\StarDestroyerBack.fbx");
        GetModelLibrary()->LoadModel("StarDestroyerTop", "Assets\\Models\\StarDestroyerTop.fbx");
        //GetTextureLibrary()->LoadTexture("Grey", )
        Application::GetCurrent().GetModelLibrary()->LoadModel("Missile", "Assets\\Models\\Missile.fbx");
       // Application::GetCurrent().GetModelLibrary()->LoadModel("StarDestroyerc", "Assets\\Models\\ShipGenMesh.fbx");
        Application::GetCurrent().GetModelLibrary()->LoadModel("Stardestroyerf", "Assets\\Models\\ReferenceHullFront.fbx");
        Application::GetCurrent().GetModelLibrary()->LoadModel("StarDestroyerm", "Assets\\Models\\ReferenceHullMid.fbx");
        Application::GetCurrent().GetModelLibrary()->LoadModel("StarDestroyerb", "Assets\\Models\\ReferenceHullBack.fbx");
        Application::GetCurrent().GetModelLibrary()->LoadModel("StarDestroyert", "Assets\\Models\\ReferenceHullTop.fbx");

        Application::GetCurrent().GetModelLibrary()->LoadModel("XWing", "Assets\\Models\\Xwing.fbx");
        Application::GetCurrent().GetModelLibrary()->LoadModel("Sphere", "Assets\\Models\\Sphere.fbx");
        Application::GetCurrent().GetTextureLibrary()->LoadTexture("XWingAlbedo", "Assets\\Textures\\xwing.jpg", TextureFormat::RGB);
        Application::GetCurrent().GetTextureLibrary()->LoadTexture("Blue", "Assets\\Textures\\Blue.png", TextureFormat::RGB);

        AddDirLight(Vector3(0.0f, 0.0f, 0.0f), Vector3(-20.0f, 10.0f, 0.0f), Vector3(1.0f, 1.0f, 0.85f), 1.0f);


        CreateStarDestroyer();

        XwingDirector::GetInstance().SpawnTestSpherePair();
        XwingDirector::GetInstance().SetCameraController();

        for (int i = 0; i < 1; i++)
        {
            XwingDirector::GetInstance().SpawnXWing();
            XwingDirector::GetInstance().SpawnMissile();
           // XwingDirector::GetInstance().SpawnMissile();

           
        }


       
       // XwingDirector::GetInstance().SpawnXWing();

       // XwingDirector::GetInstance().TempStartAll();

      

        std::string text = "ShieldGenOne : [" + std::to_string(healthGenOne) + "] % ||||" + "  ShieldGenTwo : [" + std::to_string(healthGentwo) + "] %";

        Application::GetCurrent().SetWindowTitle(text);

    }


    void OnUpdate(float deltaTime)
    {
        if(Input::InputSystem::GetInstance().GetKeyDown(Input::Key::num2))
        {
            XwingDirector::GetInstance().TempStartAll();
        }


        XwingDirector::GetInstance().Update(deltaTime);


        if (FrontMat->albedoColour.x > 0.01f)
        {
            FrontMat->albedoColour.x -= 0.4f* deltaTime;
        }
        else
        {
            FrontMat->albedoColour.x = 0.0f;
        }

        if (MidMat->albedoColour.x > 0.01f)
        {
            MidMat->albedoColour.x -= 0.4f * deltaTime;
        }
        else
        {
            MidMat->albedoColour.x = 0.0f;
        }

        if (TopMat->albedoColour.x > 0.01f)
        {
            TopMat->albedoColour.x -= 0.4f* deltaTime;
        }
        else
        {
            TopMat->albedoColour.x = 0.0f;
        }


        if (BottomMat->albedoColour.x > 0.01f)
        {
            BottomMat->albedoColour.x -= 0.4f * deltaTime;
        }
        else
        {
            BottomMat->albedoColour.x = 0.0f;
        }


        


    }





    void CreateStarDestroyer()
    {
        Entity starDestroyerEntity = GetCurrentScene()->CreateEntity("StarDestroyerF");

        SharedPtr<Mesh> stardestoyerMesh = GetModelLibrary()->GetResource("StarDestroyerFront")->GetMeshes()[0];

        starDestroyerEntity.AddComponent<MeshComponent>(stardestoyerMesh);

        FrontMat = starDestroyerEntity.AddComponent<MeshRenderer>().GetMaterial();
        FrontMat->textureMaps.albedoMap = GetTextureLibrary()->GetResource("DefaultAlbedoTexture");
        FrontMat->metallic = 0.5f;


        SharedPtr<Mesh> scolMesh = GetModelLibrary()->GetResource("Stardestroyerf")->GetMeshes()[0];
        SharedPtr<MeshCollider> collider = Factory<MeshCollider>::Create();
        collider->BuildFromMesh(scolMesh.get());




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
        properties.tag = CollisionTag::STARDESTROYER;



        RigidBody3D* body = GetPhysicsEngine()->CreateRigidBody(starDestroyerEntity, properties);


        body->m_OnCollisionCallback = std::bind(&PhysicsFinals::OnCollisionFront, this, std::placeholders::_1, std::placeholders::_2);




        starDestroyerEntity = GetCurrentScene()->CreateEntity("StarDestroyerM");

        stardestoyerMesh = GetModelLibrary()->GetResource("StarDestroyerMid")->GetMeshes()[0];

        starDestroyerEntity.AddComponent<MeshComponent>(stardestoyerMesh);

        MidMat = starDestroyerEntity.AddComponent<MeshRenderer>().GetMaterial();
        MidMat->textureMaps.albedoMap = GetTextureLibrary()->GetResource("DefaultAlbedoTexture");
        MidMat->metallic = 0.5f;
        //material->albedoColour = Vector4(1.0f, 0.0f, 0.0f,1.0f);

  
         scolMesh = GetModelLibrary()->GetResource("StarDestroyerm")->GetMeshes()[0];
         collider = Factory<MeshCollider>::Create();
        collider->BuildFromMesh(scolMesh.get());

        properties.collider = collider;

        body = GetPhysicsEngine()->CreateRigidBody(starDestroyerEntity, properties);

        body->m_OnCollisionCallback = std::bind(&PhysicsFinals::OnCollisionMid, this, std::placeholders::_1, std::placeholders::_2);

        starDestroyerEntity = GetCurrentScene()->CreateEntity("StarDestroyerB");

        stardestoyerMesh = GetModelLibrary()->GetResource("StarDestroyerBack")->GetMeshes()[0];

        starDestroyerEntity.AddComponent<MeshComponent>(stardestoyerMesh);

        BottomMat = starDestroyerEntity.AddComponent<MeshRenderer>().GetMaterial();
        BottomMat->textureMaps.albedoMap = GetTextureLibrary()->GetResource("DefaultAlbedoTexture");
        BottomMat->metallic = 0.5f;
       // material->albedoColour = Vector4(0.0f, 0.0f, 1.0f,1.0f);

         scolMesh = GetModelLibrary()->GetResource("StarDestroyerb")->GetMeshes()[0];
         collider = Factory<MeshCollider>::Create();
        collider->BuildFromMesh(scolMesh.get());


        properties.collider = collider;

        body = GetPhysicsEngine()->CreateRigidBody(starDestroyerEntity, properties);

        body->m_OnCollisionCallback = std::bind(&PhysicsFinals::OnCollisionBack, this, std::placeholders::_1, std::placeholders::_2);

        starDestroyerEntity = GetCurrentScene()->CreateEntity("StarDestroyerT");

        stardestoyerMesh = GetModelLibrary()->GetResource("StarDestroyerTop")->GetMeshes()[0];

        starDestroyerEntity.AddComponent<MeshComponent>(stardestoyerMesh);

        TopMat = starDestroyerEntity.AddComponent<MeshRenderer>().GetMaterial();
        TopMat->textureMaps.albedoMap = GetTextureLibrary()->GetResource("DefaultAlbedoTexture");
        TopMat->metallic = 0.5f;

         scolMesh = GetModelLibrary()->GetResource("StarDestroyert")->GetMeshes()[0];
        collider = Factory<MeshCollider>::Create();
        collider->BuildFromMesh(scolMesh.get());

        properties.collider = collider;

        body = GetPhysicsEngine()->CreateRigidBody(starDestroyerEntity, properties);

        body->m_OnCollisionCallback = std::bind(&PhysicsFinals::OnCollisionTop, this, std::placeholders::_1, std::placeholders::_2);

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

        if (body->m_tag == CollisionTag::MISSILE)
        {
            LOG_ERROR("MissileHit the Ship'");
        }
        
        return false;
    }

    bool OnCollisionFront(RigidBody3D* body, Vector3 collisionpoint)
    {

        if (body->m_tag == CollisionTag::MISSILE)
        {
            LOG_INFO("FRONT");
            FrontMat->albedoColour = Vector4(1.0f, 0.0f, 0.0f,1.0f);
        }

        return false;
    }

    bool OnCollisionMid(RigidBody3D* body, Vector3 collisionpoint)
    {

        if (body->m_tag == CollisionTag::MISSILE)
        {
            LOG_ERROR("MID");
            MidMat->albedoColour = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
        }

        return false;
    }

    bool OnCollisionBack(RigidBody3D* body, Vector3 collisionpoint)
    {

        if (body->m_tag == CollisionTag::MISSILE)
        {
            LOG_ERROR("BACK");
            BottomMat->albedoColour = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
        }

        return false;
    }

    bool OnCollisionTop(RigidBody3D* body, Vector3 collisionpoint)
    {

        if (body->m_tag == CollisionTag::MISSILE)
        {
            LOG_ERROR("TOP");
            TopMat->albedoColour = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
        }

        return false;
    }



    bool OnCollisionSheildGeneratorOne(RigidBody3D* body, Vector3 collisionpoint)
    {

        if (body->m_tag == CollisionTag::MISSILE)
        {
            LOG_ERROR("ShieldGen ONE :  H I T");
            healthGenOne -= 25;

            std::string text = "ShieldGenOne : [" + std::to_string(healthGenOne) + "] % ||||" + "ShieldGenTwo : [" + std::to_string(healthGentwo) + "] %";

            Application::GetCurrent().SetWindowTitle(text);
        }

        return false;
    }


    bool OnCollisionSheildGeneratorTwo(RigidBody3D* body, Vector3 collisionpoint)
    {

        if (body->m_tag == CollisionTag::MISSILE)
        {
            LOG_ERROR("ShieldGen TWO :  H I T");
            healthGentwo -= 25;

            std::string text = "ShieldGenOne : [" + std::to_string(healthGenOne) + "] % ||||" + "ShieldGenTwo : [" + std::to_string(healthGentwo) + "] %";

            Application::GetCurrent().SetWindowTitle(text);
        }

        return false;
    }

    private:


        SharedPtr<Material> FrontMat;
        SharedPtr<Material> MidMat;
        SharedPtr<Material> TopMat;
        SharedPtr<Material> BottomMat;


        int healthGenOne = 100;
        int healthGentwo = 100;


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