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

        SetUpSequenceTwo();

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
        GetTextureLibrary()->LoadTexture("AsteroidTwoAlbedo", "Assets\\Textures\\asteroidtwo.png", TextureFormat::RGB);


        GetModelLibrary()->LoadModel("Sphere", "Assets\\Models\\Sphere.fbx");
        GetModelLibrary()->LoadModel("Falcon", "Assets\\Models\\Falcon.fbx");
        GetModelLibrary()->LoadModel("Floor", "Assets\\Models\\TestFloor.fbx");
        GetModelLibrary()->LoadModel("AsteroidOne", "Assets\\Models\\AsteroidOne.fbx");
        GetModelLibrary()->LoadModel("AsteroidTwo", "Assets\\Models\\AsteroidTwo.fbx");
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

        Transform* transform = &dirLight.AddComponent<Transform>();
        transform->SetPosition(position);
        transform->SetRotation(Quaternion(Radians(rotation)));
       

        Light& light = dirLight.AddComponent<Light>();
        light.type = LightType::DirectionLight;
        light.color = color;
        light.intensity = intensity <= 0.0f ? 0.0f : intensity;
        //light.direction = Normalize(transform->GetForwardVector());


        directionLightTransform = transform;
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


     


       
    

        Sequence seqOneCamera; 

        seqOneCamera.name = "FalconFlyCamera";
        seqOneCamera.startTime = 6.98f;
        seqOneCamera.duration = 0.02f;
        seqOneCamera.objectTransform = mainCameraTransform;
        seqOneCamera.curve = false;
        seqOneCamera.play = false;

        waypoint.position = Vector3(-29.0f, 6.0f, -1.6f);
        waypoint.rotation = Vector3(-171.0f, -78.27f, 174.0);
        seqOneCamera.waypointList.push_back(waypoint);

        waypoint.position = Vector3(-117.6f, 13.51f, -46.0f);
        waypoint.rotation = Vector3(-178.31f, 8.3f, 167.2);
        seqOneCamera.waypointList.push_back(waypoint);

        sequencer->AddSequence(seqOneCamera);


        Sequence seqDirectionalLight;

        seqDirectionalLight.name = "Directional";
        seqDirectionalLight.startTime = 6.98f;
        seqDirectionalLight.duration = 0.02f;
        seqDirectionalLight.objectTransform = directionLightTransform;
        seqDirectionalLight.curve = false;
        seqDirectionalLight.play = false;

        waypoint.position = Vector3(-29.0f, 6.0f, -1.6f);
        waypoint.rotation = Vector3(-171.0f, -78.27f, 174.0f);
        seqDirectionalLight.waypointList.push_back(waypoint);

        waypoint.position = Vector3(-29.0f, 6.0f, -1.6f);
        waypoint.rotation = Vector3(-176.0f, -8.27f, 167.0);
        seqDirectionalLight.waypointList.push_back(waypoint);

        sequencer->AddSequence(seqDirectionalLight);



        sequencer->SetTotalDuration(14.0f);
    }


    void SetUpSequenceTwo()
    {

       // mainCameraTransform->SetPosition(Vector3( -120.0f, 10.0f, 48.0f));
       // mainCameraTransform->SetRotation(Vector3(0.0f, 179.0f, 0.0f));

        Entity asteroidTwoEntity = GetCurrentScene()->CreateEntity("AsteroidTwo");
        Transform* transform = &asteroidTwoEntity.AddComponent<Transform>();
        transform->SetPosition(Vector3(-102.0f, 10.0f,0.0f));
        transform->SetEularRotation(Vector3(89.0f, 0.0f, 00.0f));
        transform->SetScale(Vector3(2.0f));
        //transform.SetScale(Vector3(15.0f));

       // falconTransform = transform;

        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("AsteroidTwo")->GetMeshes()[0];
        asteroidTwoEntity.AddComponent<MeshComponent>(mesh);


        SharedPtr<Material> albedoMat = asteroidTwoEntity.AddComponent<MeshRenderer>().GetMaterial();
        albedoMat->textureMaps.albedoMap = GetTextureLibrary()->GetResource("AsteroidTwoAlbedo");
        albedoMat->type = MaterialType::Opaque;
        albedoMat->roughness = 0.0f;

        Waypoint waypoint;


        Sequence seqDodge;
        seqDodge.name = "FalconDodgeTwo";
        seqDodge.startTime = 7.00f;
        seqDodge.duration = 4.0f;
        seqDodge.objectTransform = falconTransform;
        seqDodge.curve = true;
        seqDodge.play = false;

        waypoint.position = Vector3(-118.24f, 15.0f, 21.32f);
        waypoint.rotation = Vector3(0.0f, 0.0f, -50.0f);
        seqDodge.waypointList.push_back(waypoint);

        waypoint.position = Vector3(-136.78f, 10.0f, -0.62f);
        waypoint.rotation = Vector3(20.0f, 0.0f, -89.0f);
        seqDodge.waypointList.push_back(waypoint);

        waypoint.position = Vector3(-140.6f, 15.0f, 7.5f);
        waypoint.rotation = Vector3(-10.0f, 0.0f, 60.0f);
        seqDodge.waypointList.push_back(waypoint);

        waypoint.position = Vector3(-122.81f, 10.0f, -23.0f);
        waypoint.rotation = Vector3(-30.0f, 0.0f, 80.0f);
        seqDodge.waypointList.push_back(waypoint);

        sequencer->AddSequence(seqDodge);



        Sequence seqDodgeTwo;
        seqDodgeTwo.name = "FalconDodgeTwo";
        seqDodgeTwo.startTime = 11.00f;
        seqDodgeTwo.duration = 2.0f;
        seqDodgeTwo.objectTransform = falconTransform;

        seqDodgeTwo.curve = false;
        seqDodgeTwo.play = false;


      

        waypoint.position = Vector3(-122.81f, 10.0f, -23.0f);
        waypoint.rotation = Vector3(-30.0f, 00.0f, 80.0f);
        seqDodgeTwo.waypointList.push_back(waypoint);

        waypoint.position = Vector3(-97.6f, 15.0f, -66.0f);
        waypoint.rotation = Vector3(-30.0f, 0.0f, 80.0f);
        seqDodgeTwo.waypointList.push_back(waypoint);

        sequencer->AddSequence(seqDodgeTwo);



        Sequence seqAsteroidRotate;
        seqAsteroidRotate.name = "Asteroidrotate";
        seqAsteroidRotate.startTime = 7.0f;
        seqAsteroidRotate.duration = 9.0f;
        seqAsteroidRotate.objectTransform = transform;
        seqAsteroidRotate.curve = false;
        seqAsteroidRotate.play = false;

        waypoint.position = Vector3(-102.84f, 16.0f, -12.5f);
        waypoint.rotation = Vector3(-40.0f, 0.0f, 0.0f);
        seqAsteroidRotate.waypointList.push_back(waypoint);

        waypoint.position = Vector3(-112.0f, 10.0f, 12.0f);
       // waypoint.position = Vector3(-107.0f, 10.0f, 23.0f));
        waypoint.rotation = Vector3(0.0f, 20.0f, 0.0f);
        seqAsteroidRotate.waypointList.push_back(waypoint);


        sequencer->AddSequence(seqAsteroidRotate);


    }

    SharedPtr<Sequencer> sequencer;
    bool playSequencer;
    Transform* mainCameraTransform = nullptr;
    Transform* falconTransform = nullptr;
    Transform* directionLightTransform = nullptr;
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