#include "GameEngine.h"
#include "Animation/AnimationCurve.h"
#include "Animation/Sequencer.h"

using namespace FanshaweGameEngine::Animation;
using namespace FanshaweGameEngine;

class FrameworkFinals : public Application
{

    void OnInit()
    {

        LoadModels();
        AddDirLight(Vector3(0.0f, 0.0f, 0.0f), Vector3(-20.0f, 20.0f, 0.0f), Vector3(1.0f, 1.0f, 1.00f), 1.0f);

        sequencer = Factory<Sequencer>::Create();
        SetupTestFloor();
        SetUpSequenceOne();

    }


    void OnUpdate(float deltaTime)
    {
        if (Input::InputSystem::GetInstance().GetKeyDown(Input::Key::G))
        {
            playSequencer = !playSequencer;
        }


        if (playSequencer)
        {
            sequencer->Update(deltaTime);
        }
    }


    void LoadModels()
    {
        GetTextureLibrary()->LoadTexture("Grass", "Assets\\Textures\\grass.png", TextureFormat::RGB);


        GetModelLibrary()->LoadModel("Sphere", "Assets\\Models\\Sphere.fbx");
        GetModelLibrary()->LoadModel("Falcon", "Assets\\Models\\Falcon.fbx");
        GetModelLibrary()->LoadModel("Floor", "Assets\\Models\\TestFloor.fbx");
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


    void SetupTestFloor()
    {

        Entity sphereEntity = GetCurrentScene()->CreateEntity("Floor");
        Transform* transform = &sphereEntity.AddComponent<Transform>();
        transform->SetPosition(Vector3(00.0f, 0.0f, 0.0f));


        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("Floor")->GetMeshes()[0];
        sphereEntity.AddComponent<MeshComponent>(mesh);

        SharedPtr<Material> mat = sphereEntity.AddComponent<MeshRenderer>().GetMaterial();

        mat->textureMaps.albedoMap = GetTextureLibrary()->GetResource("Grass");
       // mat->albedoColour = Vector4(1.0f, 0.0f, 0.4f, 1.0f);
        mat->type = MaterialType::Opaque;
        mat->metallic = 0.0f;
        mat->roughness = 0.0f;

    }

    void SetUpSequenceOne()
    {

        // Sequence One
        
        Entity sphereEntity = GetCurrentScene()->CreateEntity("Falcon");
        Transform* transform = &sphereEntity.AddComponent<Transform>();
        transform->SetPosition(Vector3(0.0f, 5.0f, 0.0f));
        transform->SetScale(Vector3(0.05f));
        

        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("Falcon")->GetMeshes()[0];
        sphereEntity.AddComponent<MeshComponent>(mesh);

        SharedPtr<Material> mat = sphereEntity.AddComponent<MeshRenderer>().GetMaterial();
        mat->metallic = 0.0f;
        mat->roughness = 0.0f;



        Sequence seqOne;
        seqOne.name = "SphereFly";
        seqOne.startTime = 2.0f;
        seqOne.duration = 5.0f;
        seqOne.objectTransform = transform;

        seqOne.play = false;

        Waypoint waypoint;
     /*   waypoint.position = Vector3(10.0f, 5.0f, 0.0f);
        waypoint.rotation = Quaternion(Radians(Vector3(0.0f, 0.0f, 0.0f)));

        seqOne.waypointList.push_back(waypoint);
        waypoint.position = Vector3(30.0f, 0.0f, 0.0f);
        waypoint.rotation = Quaternion(Radians(Vector3(0.0f, 0.0f, 0.0f)));

        seqOne.waypointList.push_back(waypoint);*/

        waypoint.position = Vector3(0.0f, 5.0f, 0.0f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqOne.waypointList.push_back(waypoint);

        waypoint.position = Vector3(5.5f, 5.0f, -3.5f);
        waypoint.rotation = Vector3(0.0f, -55.0f, 0.0f);
        seqOne.waypointList.push_back(waypoint);

        waypoint.position = Vector3(30.0f, 5.0f, -15.0f);
        waypoint.rotation = Vector3(0.0f, -179.0f, 0.0f);
        seqOne.waypointList.push_back(waypoint);

        waypoint.position = Vector3(30.0f, 5.0f, 0.0f);
        waypoint.rotation = Vector3(0.0f, -179.0f, 0.0f);
        seqOne.waypointList.push_back(waypoint);

        sequencer->AddSequence(seqOne);

    }


    SharedPtr<Sequencer> sequencer;
    bool playSequencer;

};




int main(int argc, char* argv)
{
    // Creating a new Appinstance
    FrameworkFinals* app = new FrameworkFinals();

    //FilePath path = File::GetCurrentPath();

    // Always Initialize the App
    app->Initialize();
    // Running the Application
    app->Run();


    delete app;
}