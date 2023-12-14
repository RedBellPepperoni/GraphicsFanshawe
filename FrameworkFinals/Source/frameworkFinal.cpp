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
        AddDirLight(Vector3(0.0f, 0.0f, 0.0f), Vector3(-20.0f, -75.0f, 0.0f), Vector3(1.0f, 1.0f, 1.00f), 1.0f);

        sequencer = Factory<Sequencer>::Create();
       // SetupTestFloor();
        AddMainCamera();
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
        GetTextureLibrary()->LoadTexture("AsteroidOneAlbedo", "Assets\\Textures\\asteroidone.png", TextureFormat::RGB);


        GetModelLibrary()->LoadModel("Sphere", "Assets\\Models\\Sphere.fbx");
        GetModelLibrary()->LoadModel("Falcon", "Assets\\Models\\Falcon.fbx");
        GetModelLibrary()->LoadModel("Floor", "Assets\\Models\\TestFloor.fbx");
        GetModelLibrary()->LoadModel("AsteroidOne", "Assets\\Models\\AsteroidOne.fbx");
    }

    void AddMainCamera()
    {
        Entity cameraEntity = GetCurrentScene()->GetEntityManager()->Create("MainCamera");
        Camera* camera = &cameraEntity.AddComponent<Camera>();
        Transform* transform = &cameraEntity.AddComponent<Transform>();

        //AudioListener* listener = &cameraEntity.AddComponent<Audio::AudioListener>(transform);

        transform->SetPosition(Vector3(-29.0f, 6.0f, -1.6f));
        transform->SetEularRotation(Vector3(-171.0f, -78.27f, 174.0f));

        cameraEntity.AddComponent<DefaultCameraController>(DefaultCameraController::CameraType::FlyCam);
        
        mainCameraTransform = transform;
    
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

        // Sapwning the FALCON ======================
        
        Entity falconEntity = GetCurrentScene()->CreateEntity("Falcon");
        Transform* transform = &falconEntity.AddComponent<Transform>();
        transform->SetPosition(Vector3(0.0f, 5.0f, 40.0f));
        transform->SetEularRotation(Vector3(00.0f, 0.0f, 00.0f));
        transform->SetScale(Vector3(0.05f));
        
        falconTransform = transform;

        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("Falcon")->GetMeshes()[0];
        falconEntity.AddComponent<MeshComponent>(mesh);

        SharedPtr<Material> mat = falconEntity.AddComponent<MeshRenderer>().GetMaterial();
        mat->metallic = 0.0f;
        mat->roughness = 0.0f;

        // =================Spawning the BIG asteroid ====================================

        Entity asteroidOneEntity = GetCurrentScene()->CreateEntity("AsteroidBigOne");
        Transform* asteroidtransform = &asteroidOneEntity.AddComponent<Transform>();
       // asteroidtransform->SetPosition(Vector3(1.2f, 5.0f, -9.5f));
        asteroidtransform->SetPosition(Vector3(-1.2f, 5.0f, -30.5f));
        asteroidtransform->SetEularRotation(Vector3(00.0f, 0.0f, 00.0f));
        asteroidtransform->SetScale(Vector3(1.0f));


        mesh = GetModelLibrary()->GetResource("AsteroidOne")->GetMeshes()[0];
        asteroidOneEntity.AddComponent<MeshComponent>(mesh);

       SharedPtr<Material> albedoMat = asteroidOneEntity.AddComponent<MeshRenderer>().GetMaterial();
       albedoMat->textureMaps.albedoMap = GetTextureLibrary()->GetResource("AsteroidOneAlbedo");
       albedoMat->type = MaterialType::Opaque;
       albedoMat->roughness = 0.0f;

        // ===================== Initial fly Sequence ===============================
        Sequence seqOne;
        seqOne.name = "FalconInitFly";
        seqOne.startTime = 0.0f;
        seqOne.duration = 2.0f;
        seqOne.objectTransform = transform;
        seqOne.curve = false;
        seqOne.play = false;

        Waypoint waypoint;

        waypoint.position = Vector3(0.0f, 5.0f, 50.0f);
        waypoint.rotation = Vector3(0.0f,0.0f, 0.0f);
        seqOne.waypointList.push_back(waypoint);

        waypoint.position = Vector3(0.0f, 5.0f, 24.0f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 10.0f);
        seqOne.waypointList.push_back(waypoint);

        sequencer->AddSequence(seqOne);


        // ===================== DODGE Sequence ===============================
        Sequence seqDodge;
        seqDodge.name = "FalconDodge";
        seqDodge.startTime = 2.01f;
        seqDodge.duration = 5.0f;
        seqDodge.objectTransform = falconTransform;
        seqDodge.curve = true;
        seqDodge.play = false; 
   
        waypoint.position = Vector3(0.0f, 5.0f, 24.0f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 10.0f);
        seqDodge.waypointList.push_back(waypoint);

        waypoint.position = Vector3(0.0f,7.0f, -7.5f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 40.0f);
        seqDodge.waypointList.push_back(waypoint);

        waypoint.position = Vector3(-32.0f, 8.0f, 14.0f);
        waypoint.rotation = Vector3(0.0f,0.0f, -80.0f);
        seqDodge.waypointList.push_back(waypoint);

        waypoint.position = Vector3(0.0f, 5.0f, -48.0f);
        waypoint.rotation = Vector3(0.0f, 0.0f, -50.0f);
        seqDodge.waypointList.push_back(waypoint);

        sequencer->AddSequence(seqDodge);





        Sequence seqAsteroidRotate;
        seqAsteroidRotate.name = "Asteroidrotate";
        seqAsteroidRotate.startTime = 0.0f;
        seqAsteroidRotate.duration = 8.0f;
        seqAsteroidRotate.objectTransform = asteroidtransform;
        seqAsteroidRotate.curve = false;
        seqAsteroidRotate.play = false;

        waypoint.position = Vector3(-1.2f, 5.0f, -40.5f);
        waypoint.rotation = Vector3(0.0f, 20.0f, 10.0f);
        seqAsteroidRotate.waypointList.push_back(waypoint);

        waypoint.position = Vector3(1.2f, 2.0f, 10.5f);
        waypoint.rotation = Vector3(0.0f, 179.0f, 40.0f);
        seqAsteroidRotate.waypointList.push_back(waypoint);


        sequencer->AddSequence(seqAsteroidRotate);


        sequencer->SetTotalDuration(7.0f);

   /*     Sequence seqOneCamera;

        seqOneCamera.name = "FalconFlyCamera";
        seqOneCamera.startTime = 0.0f;
        seqOneCamera.duration = 5.0f;
        seqOneCamera.objectTransform = mainCameraTransform;
        seqOneCamera.curve = false;
        seqOneCamera.play = false;

        waypoint.position = Vector3(30.05f, -6.0f, -43.44f);
        waypoint.rotation = Vector3(170.0f, -5.0f, 180.0f);
        seqOneCamera.waypointList.push_back(waypoint);

        waypoint.position = Vector3(60.05f, -6.0f, -43.44f);
        waypoint.rotation = Vector3(170.0f, -6.0f, 180.0f);
        seqOneCamera.waypointList.push_back(waypoint);

        sequencer->AddSequence(seqOneCamera);*/
    }


    SharedPtr<Sequencer> sequencer;
    bool playSequencer;
    Transform* mainCameraTransform = nullptr;
    Transform* falconTransform = nullptr;

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