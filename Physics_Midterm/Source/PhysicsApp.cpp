#include "GameEngine.h"
#include <functional>
#include "Asteroid.h"
#include "Explosion.h"

using namespace Physics;




class PhysicsApp : public Application
{
    int sphereCount = 0;
    int boxCount = 0;
    SharedPtr<Model> sphereModel;
    SharedPtr<Model> boxModel;
    SharedPtr<Model> asteroidOne;
    SharedPtr<Model> asteroidTwo;
    SharedPtr<Model> simpleCollider;
    SharedPtr<Explosion> exp;


    std::vector<SharedPtr<Asteroid>> asteroidList;

    std::vector<RigidBody3D*> asteroids;
    
   

    
    int asteroidCount = 0;

    bool pausePhysics = false;

    
    RigidBody3D* AddSphereCollider(const Vector3& position, float radius)
    {


        std::string name = "SphereEntity_" + std::to_string(sphereCount);
        Entity Object = GetCurrentScene()->CreateEntity(name);
        // Add a Trasnform. later make sure every spawnd entity has an auto attached transform

        Object.AddComponent<Transform>();

        Transform* transform = &Object.GetComponent<Transform>();
        transform->SetPosition(position);
        transform->SetScale(Vector3(radius));
        Object.AddComponent<MeshComponent>(sphereModel->GetMeshes()[0]);
        Object.AddComponent<MeshRenderer>();
        

        PhysicsProperties properties;

        properties.position = position;
        properties.stationary = false;
        properties.isStatic = false;
        properties.mass = 50.0f;


        LOG_ERROR("{0}",sphereModel->GetMeshes()[0]->GetName());

        RigidBody3D* body = &Object.AddComponent<RigidBody3D>(properties);


        SphereCollider* collider = &Object.AddComponent<SphereCollider>();
        
        collider->SetRadius(radius);

//        float Testradius = collider->GetRadius();

        body->SetCollider(*collider);

        sphereCount++;

        return body;

    }

    RigidBody3D* AddBoxCollider(const Vector3& position,const Vector3& halfSize)
    {


        std::string name = "BoxEntity_" + std::to_string(boxCount);
        Entity Object = GetCurrentScene()->CreateEntity(name);
        // Add a Trasnform. later make sure every spawnd entity has an auto attached transform

        Object.AddComponent<Transform>();

        Transform* transform = &Object.GetComponent<Transform>();
        transform->SetPosition(position);
        transform->SetScale(halfSize * 2.0f);
        Object.AddComponent<MeshComponent>(boxModel->GetMeshes()[0]);
        Object.AddComponent<MeshRenderer>();


        PhysicsProperties properties;

        properties.position = position;
        properties.stationary = false;
        properties.isStatic = false;
        properties.mass = 50.0f;


        LOG_ERROR("{0}", sphereModel->GetMeshes()[0]->GetName());

        RigidBody3D* body = &Object.AddComponent<RigidBody3D>(properties);


        BoxCollider* collider = &Object.AddComponent<BoxCollider>();

        collider->SetHalfDimensions(halfSize);


        body->SetCollider(*collider);

        boxCount++;

        return body;

    }



    void SpawnShip()
    {
        Entity Object = GetCurrentScene()->CreateEntity("SpaceStation");
        // Add a Trasnform. later make sure every spawnd entity has an auto attached transform

        SharedPtr<Model> ship = GetModelLibrary()->LoadModel("Ship", "Assets\\SM_Ship_Massive_Transport_01_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(ship);

        Object.AddComponent<Transform>();
        Object.GetComponent<Transform>().SetPosition(Vector3(0.0f));
        Object.GetComponent<Transform>().SetScale(Vector3(0.01, 0.01, 0.01));
        Object.AddComponent<MeshComponent>(ship->GetMeshes()[0]);
        Object.AddComponent<MeshRenderer>();


        simpleCollider = GetModelLibrary()->LoadModel("ShipCollider", "Assets\\ShipMesh.ply");
        CHECKNULL(simpleCollider);



        Object = GetCurrentScene()->CreateEntity("SpaceCollider");
        // Add a Trasnform. later make sure every spawnd entity has an auto attached transform


        Object.AddComponent<Transform>();
        Object.GetComponent<Transform>().SetPosition(Vector3(0.0f));
        Object.GetComponent<Transform>().SetScale(Vector3(1, 1, 1));
       // Object.AddComponent<MeshComponent>(simpleCollider->GetMeshes()[0]);
        Object.AddComponent<MeshRenderer>();

        PhysicsProperties properties;

        properties.position = Vector3(0.0f);
        properties.stationary = false;
        properties.isStatic = false;
        properties.mass = 5000.0f;


        RigidBody3D* body = &Object.AddComponent<RigidBody3D>(properties);


        MeshCollider* collider = &Object.AddComponent<MeshCollider>();
        collider->BuildFromMesh(simpleCollider->GetMeshes()[0].get());

        body->SetCollider(*collider);



    }



    void OnInit()
    {

       

        SharedPtr<Model> planemodel = GetModelLibrary()->LoadModel("Plane", "Assets\\floor.ply");
        CHECKNULL(planemodel);

        Entity PlaneObject = GetCurrentScene()->CreateEntity("PlaneOne");
        PlaneObject.AddComponent<Transform>();
        PlaneObject.GetComponent<Transform>().SetPosition(Vector3(-30.0, 0.0, -30.0));
        PlaneObject.GetComponent<Transform>().SetScale(Vector3(20.0, 1.0, 20.0));
        PlaneObject.AddComponent<MeshComponent>(planemodel->GetMeshes()[0]);
        PlaneObject.AddComponent<MeshRenderer>();



        sphereModel = GetModelLibrary()->LoadModel("Sphere", "Assets\\SphereBlender.ply");
        CHECKNULL(sphereModel);   

        boxModel = GetModelLibrary()->LoadModel("Box", "Assets\\UnitBox.ply");
        CHECKNULL(boxModel);
        
        asteroidOne = GetModelLibrary()->LoadModel("AsteroidOne", "Assets\\Asteroid_011_x10_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(asteroidOne);



        asteroidTwo = GetModelLibrary()->LoadModel("ASteroidTwo", "Assets\\Asteroid_015_x10_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(asteroidTwo);


        

        SpawnShip();

        
       
     

       //AddBoxCollider(Vector3(0.0f, 0.0f, 40.0f), Vector3(30.0f,50.0f, 80.0f));

       // AddSphereCollider(Vector3(100.0f, 5.0f, 0.0f),8.0f);



        exp = MakeShared<Explosion>();
        

         asteroidList.push_back(MakeShared<Asteroid>("ASter1",asteroidOne, Vector3(200.0f, 5.0f, 0.0f)));
         asteroidList.push_back(MakeShared<Asteroid>("ASter1",asteroidOne, Vector3(210.0f, 100.0f, 40.0f)));
         asteroidList.push_back(MakeShared<Asteroid>("ASter1",asteroidOne, Vector3(200.0f, 50.0f, 200.0f)));
         asteroidList.push_back(MakeShared<Asteroid>("ASter1",asteroidOne, Vector3(200.0f, 5.0f, 300.0f)));
 
       

      
        
       
    }

    void OnUpdate(float deltaTime)
    {
        if (Input::InputSystem::GetInstance().GetKeyDown(Input::Key::G))
        {
            pausePhysics = !pausePhysics;
            Application::GetCurrent().StartPhysics(pausePhysics);

        }


        for (SharedPtr<Asteroid> asteroid : asteroidList)
        {
            asteroid->Update(deltaTime);
        }

    }


};


int main(int argc, char* argv)
{
    // Creating a new Appinstance
    PhysicsApp* app = new PhysicsApp();

    //FilePath path = File::GetCurrentPath();

    // Always Initialize the App
    app->Initialize();
    // Running the Application
    app->Run();


    delete app;
}