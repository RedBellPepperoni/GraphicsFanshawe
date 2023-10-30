#include "GameEngine.h"


using namespace Physics;

class PhysicsApp : public Application
{
    int sphereCount = 0;
    SharedPtr<Model> sphereModel;

    bool startPhysics = true;

    
    void SpawnSphere(const Vector3& position)
    {


        std::string name = "SphereEntity_" + std::to_string(sphereCount);
        Entity Object = GetCurrentScene()->CreateEntity(name);
        // Add a Trasnform. later make sure every spawnd entity has an auto attached transform

        Object.AddComponent<Transform>();
        Object.GetComponent<Transform>().SetPosition(position);
        Object.AddComponent<MeshComponent>(sphereModel->GetMeshes()[0]);
        Object.AddComponent<MeshRenderer>();

        PhysicsProperties properties;

        properties.position = position;
        properties.stationary = false;
        properties.isStatic = false;
        properties.m_invMass = 0.1f;

        Object.AddComponent<RigidBody3D>(properties);

        sphereCount++;

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


        sphereModel = GetModelLibrary()->LoadModel("Ball", "Assets\\icosphere.ply");
        CHECKNULL(sphereModel);



        SpawnSphere(Vector3(0.0f, 20.0f, 0.0f));
        SpawnSphere(Vector3(5.0f, 20.0f, 0.0f));
        SpawnSphere(Vector3(-5.0f, 20.0f, 0.0f));
        SpawnSphere(Vector3(0.0f, 20.0f, 5.0f));
        SpawnSphere(Vector3(0.0f, 20.0f, -5.0f));
       
    }

    void OnUpdate(float deltaTime)
    {
        if (Input::InputSystem::GetInstance().GetKeyDown(Input::Key::G))
        {
            startPhysics = !startPhysics;
            Application::GetCurrent().StartPhysics(startPhysics);

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