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
        SetUpSequenceThree();
        SetUpSequenceFour();


        sequencer->SetTotalDuration(23.0f);
        sequencer->SetSeek(20.0f);
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
        GetTextureLibrary()->LoadTexture("BlastAlbedo", "Assets\\Textures\\Blast.tga", TextureFormat::RGBA);


        GetModelLibrary()->LoadModel("Sphere", "Assets\\Models\\Sphere.fbx");
        GetModelLibrary()->LoadModel("Falcon", "Assets\\Models\\Falcon.fbx");
        GetModelLibrary()->LoadModel("Floor", "Assets\\Models\\TestFloor.fbx");
        GetModelLibrary()->LoadModel("AsteroidOne", "Assets\\Models\\AsteroidOne.fbx");
        GetModelLibrary()->LoadModel("AsteroidTwo", "Assets\\Models\\AsteroidTwo.fbx");
        GetModelLibrary()->LoadModel("TieFighter", "Assets\\Models\\TieFighter.fbx");
        GetModelLibrary()->LoadModel("Blast", "Assets\\Models\\BlastPlane.fbx");

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
        BigAsteroidOneTransform = &asteroidOneEntity.AddComponent<Transform>();
       // asteroidtransform->SetPosition(Vector3(1.2f, 5.0f, -9.5f));
        BigAsteroidOneTransform->SetPosition(Vector3(-1.2f, 5.0f, -30.5f));
        BigAsteroidOneTransform->SetEularRotation(Vector3(00.0f, 0.0f, 00.0f));
        BigAsteroidOneTransform->SetScale(Vector3(1.0f));


        mesh = GetModelLibrary()->GetResource("AsteroidOne")->GetMeshes()[0];
        asteroidOneEntity.AddComponent<MeshComponent>(mesh);

       SharedPtr<Material> albedoMat = asteroidOneEntity.AddComponent<MeshRenderer>().GetMaterial();
       albedoMat->textureMaps.albedoMap = GetTextureLibrary()->GetResource("AsteroidOneAlbedo");
       albedoMat->type = MaterialType::Opaque;
       albedoMat->roughness = 0.0f;






       Entity asteroidTwo = GetCurrentScene()->CreateEntity("AsteroidFiller");
       filleOneTransform = &asteroidTwo.AddComponent<Transform>();
       // asteroidtransform->SetPosition(Vector3(1.2f, 5.0f, -9.5f));
       filleOneTransform->SetPosition(Vector3(23.2f, 10.0f, -46.5f));
       filleOneTransform->SetEularRotation(Vector3(00.0f, 0.0f, 00.0f));
       filleOneTransform->SetScale(Vector3(0.5f));
       asteroidTwo.AddComponent<MeshComponent>(mesh);
       albedoMat = asteroidTwo.AddComponent<MeshRenderer>().GetMaterial();
       albedoMat->textureMaps.albedoMap = GetTextureLibrary()->GetResource("AsteroidOneAlbedo");
       albedoMat->type = MaterialType::Opaque;
       albedoMat->roughness = 0.0f;


       Entity asteroidThrree = GetCurrentScene()->CreateEntity("AsteroidFiller2");
       filleTwoTransform = &asteroidThrree.AddComponent<Transform>();
       filleTwoTransform->SetPosition(Vector3(23.2f, 20.0f, -50.5f));
       filleTwoTransform->SetEularRotation(Vector3(00.0f, 0.0f, 60.0f));
       filleTwoTransform->SetScale(Vector3(0.5f));
       asteroidThrree.AddComponent<MeshComponent>(mesh);
       albedoMat = asteroidThrree.AddComponent<MeshRenderer>().GetMaterial();
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
        seqAsteroidRotate.objectTransform = BigAsteroidOneTransform;
        seqAsteroidRotate.curve = false;
        seqAsteroidRotate.play = false;

        waypoint.position = Vector3(-1.2f, 5.0f, -40.5f);
        waypoint.rotation = Vector3(0.0f, 20.0f, 10.0f);
        seqAsteroidRotate.waypointList.push_back(waypoint);

        waypoint.position = Vector3(1.2f, 2.0f, 10.5f);
        waypoint.rotation = Vector3(0.0f, 179.0f, 40.0f);
        seqAsteroidRotate.waypointList.push_back(waypoint);


        sequencer->AddSequence(seqAsteroidRotate);


        Sequence seqAsteroidEnd;
        seqAsteroidEnd.name = "Asteroidrotate";
        seqAsteroidEnd.startTime = 8.0f;
        seqAsteroidEnd.duration = 0.5f;
        seqAsteroidEnd.objectTransform = BigAsteroidOneTransform;
        seqAsteroidEnd.curve = false;
        seqAsteroidEnd.play = false;

        waypoint.position = Vector3(0.0f, 5000.0f, 00.5f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqAsteroidEnd.waypointList.push_back(waypoint);

        waypoint.position = Vector3(0.0f, 5000.0f, 00.5f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqAsteroidEnd.waypointList.push_back(waypoint);


        sequencer->AddSequence(seqAsteroidEnd);


     
        Sequence seqOneCamera;

        seqOneCamera.name = "FalconFlyCamera";
        seqOneCamera.startTime = 0.0f;
        seqOneCamera.duration = 6.5f;
        seqOneCamera.objectTransform = mainCameraTransform;
        seqOneCamera.curve = false;
        seqOneCamera.play = false;

        waypoint.position = Vector3(-29.0f, 6.0f, -1.6f);
        waypoint.rotation = Vector3(-171.0f, -78.27f, 174.0f);
        seqOneCamera.waypointList.push_back(waypoint);

        waypoint.position = Vector3(-29.0f, 6.1f, -1.6f);
        waypoint.rotation = Vector3(-171.0f, -78.27f, 174.0f);
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


        Sequence seqFillerAsteroindOne;
        seqFillerAsteroindOne.name = "Directional";
        seqFillerAsteroindOne.startTime = 0.98f;
        seqFillerAsteroindOne.duration = 6.0f;
        seqFillerAsteroindOne.objectTransform = filleOneTransform;
        seqFillerAsteroindOne.curve = false;
        seqFillerAsteroindOne.play = false;
        waypoint.position = Vector3(23.2f, 10.0f, -46.5f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqFillerAsteroindOne.waypointList.push_back(waypoint);
        waypoint.position = Vector3(23.0f, 6.0f, 62.6f);
        waypoint.rotation = Vector3((30.0f, 60.0f, 0.0f));
        seqFillerAsteroindOne.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqFillerAsteroindOne);


        Sequence seqFillerAsteroindtwo;
        seqFillerAsteroindtwo.name = "Directional";
        seqFillerAsteroindtwo.startTime = 0.0f;
        seqFillerAsteroindtwo.duration = 7.0f;
        seqFillerAsteroindtwo.objectTransform = filleTwoTransform;
        seqFillerAsteroindtwo.curve = false;
        seqFillerAsteroindtwo.play = false;
        waypoint.position = Vector3(23.2f, -5.0f, -50.5f);
        waypoint.rotation = Vector3(60.0f, 00.0f, 0.0f);
        seqFillerAsteroindtwo.waypointList.push_back(waypoint);
        waypoint.position = Vector3(23.0f, -8.0f, 50.6f);
        waypoint.rotation = Vector3((-60.0f, 0.0f, 0.0f));
        seqFillerAsteroindtwo.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqFillerAsteroindtwo);




    
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




        Entity tieOne = GetCurrentScene()->CreateEntity("TieOne");
        tieOneTransform = &tieOne.AddComponent<Transform>();
        tieOneTransform->SetPosition(Vector3(-121.24f, 15.0f, 26.32f));
        tieOneTransform->SetEularRotation(Vector3(0.0f, 0.0f, 00.0f));
        tieOneTransform->SetScale(Vector3(0.6f));
        mesh = GetModelLibrary()->GetResource("TieFighter")->GetMeshes()[0];
        tieOne.AddComponent<MeshComponent>(mesh);
        albedoMat = tieOne.AddComponent<MeshRenderer>().GetMaterial();
        albedoMat->type = MaterialType::Opaque;
        albedoMat->roughness = 0.0f;



        Entity tieTwo = GetCurrentScene()->CreateEntity("TieTwo");
        tieTwoTransform = &tieTwo.AddComponent<Transform>();
        tieTwoTransform->SetPosition(Vector3(-121.24f, 15.0f, 26.32f));
        tieTwoTransform->SetEularRotation(Vector3(0.0f, 0.0f, 00.0f));
        tieTwoTransform->SetScale(Vector3(0.6f));
        tieTwo.AddComponent<MeshComponent>(mesh);
        albedoMat = tieTwo.AddComponent<MeshRenderer>().GetMaterial();
        albedoMat->type = MaterialType::Opaque;
        albedoMat->roughness = 0.0f;



        Entity tieThree = GetCurrentScene()->CreateEntity("TieThree");
        tieThreeTransform = &tieThree.AddComponent<Transform>();
        tieThreeTransform->SetPosition(Vector3(-118.24f, -10.0f, 25.32f));
        tieThreeTransform->SetEularRotation(Vector3(0.0f, 0.0f, 00.0f));
        tieThreeTransform->SetScale(Vector3(0.6f));
        tieThree.AddComponent<MeshComponent>(mesh);
        albedoMat = tieThree.AddComponent<MeshRenderer>().GetMaterial();
        albedoMat->type = MaterialType::Opaque;
        albedoMat->roughness = 0.0f;


        // Tie 4 spawn
        Entity tieFour = GetCurrentScene()->CreateEntity("TieThree");
        tieFourTransform = &tieFour.AddComponent<Transform>();
        tieFourTransform->SetPosition(Vector3(-118.24f, -10.0f, 25.32f));
        tieFourTransform->SetEularRotation(Vector3(0.0f, 0.0f, 00.0f));
        tieFourTransform->SetScale(Vector3(0.6f));
        tieFour.AddComponent<MeshComponent>(mesh);
        albedoMat = tieFour.AddComponent<MeshRenderer>().GetMaterial();
        albedoMat->type = MaterialType::Opaque;
        albedoMat->roughness = 0.0f;






        Waypoint waypoint;


        Sequence seqTwoCamera;

        seqTwoCamera.name = "FalconFlyCamera";
        seqTwoCamera.startTime = 6.98f;
        seqTwoCamera.duration = 8.0f;
        seqTwoCamera.objectTransform = mainCameraTransform;
        seqTwoCamera.curve = false;
        seqTwoCamera.play = false;

        waypoint.position = Vector3(-117.6f, 13.51f, -46.0f);
        waypoint.rotation = Vector3(-178.31f, 8.3f, 167.2);
        seqTwoCamera.waypointList.push_back(waypoint);

        waypoint.position = Vector3(-117.6f, 13.5f, -46.0f);
        waypoint.rotation = Vector3(-178.31f, 8.3f, 167.2);
        seqTwoCamera.waypointList.push_back(waypoint);

        sequencer->AddSequence(seqTwoCamera);





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
        waypoint.rotation = Vector3(0.0f, 20.0f, 0.0f);
        seqAsteroidRotate.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqAsteroidRotate);




        // Tie fighter One 

        Sequence seqTieOne;
        seqTieOne.name = "FalconDodgeTwo";
        seqTieOne.startTime = 9.0f;
        seqTieOne.duration = 4.0f;
        seqTieOne.objectTransform = tieOneTransform;
        seqTieOne.curve = true;
        seqTieOne.play = false;
        waypoint.position = Vector3(-121.24f, 15.0f, 26.32f);
        waypoint.rotation = Vector3(0.0f, 0.0f, -50.0f);
        seqTieOne.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-134.78f, 25.0f, 3.62f);
        waypoint.rotation = Vector3(20.0f, 0.0f, -60.0f);
        seqTieOne.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-138.6f, 15.0f, 7.9f);
        waypoint.rotation = Vector3(-10.0f, 0.0f, 40.0f);
        seqTieOne.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-122.81f, 10.0f, -23.0f);
        waypoint.rotation = Vector3(-30.0f, 0.0f, 70.0f);
        seqTieOne.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqTieOne);



        Sequence seqTieOneEnd;
        seqTieOneEnd.name = "FalconDodgeTwo";
        seqTieOneEnd.startTime = 13.00f;
        seqTieOneEnd.duration = 2.0f;
        seqTieOneEnd.objectTransform = tieOneTransform;
        seqTieOneEnd.curve = false;
        seqTieOneEnd.play = false;
        waypoint.position = Vector3(-122.81f, 10.0f, -23.0f);
        waypoint.rotation = Vector3(-30.0f, 00.0f, 70.0f);
        seqTieOneEnd.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-99.6f, 15.0f, -66.0f);
        waypoint.rotation = Vector3(-30.0f, 0.0f, 150.0f);
        seqTieOneEnd.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqTieOneEnd);



        // Tie fighter Two


        Sequence seqTieTwo;
        seqTieTwo.name = "TieTwoStart";
        seqTieTwo.startTime = 9.5f;
        seqTieTwo.duration = 4.0f;
        seqTieTwo.objectTransform = tieTwoTransform;
        seqTieTwo.curve = true;
        seqTieTwo.play = false;
        waypoint.position = Vector3(-118.24f, -5.0f, 25.32f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 50.0f);
        seqTieTwo.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-143.78f, 0.0f, -4.62f);
        waypoint.rotation = Vector3(20.0f, 0.0f, 60.0f);
        seqTieTwo.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-139.6f, 10.0f, 8.9f);
        waypoint.rotation = Vector3(-10.0f, 0.0f, -40.0f);
        seqTieTwo.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-122.81f, -1.0f, -23.0f);
        waypoint.rotation = Vector3(30.0f, 0.0f, -70.0f);
        seqTieTwo.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqTieTwo);



        Sequence seqTieTwoEnd;
        seqTieTwoEnd.name = "TieTwoEnd";
        seqTieTwoEnd.startTime = 13.50f;
        seqTieTwoEnd.duration = 2.0f;
        seqTieTwoEnd.objectTransform = tieTwoTransform;
        seqTieTwoEnd.curve = false;
        seqTieTwoEnd.play = false;
        waypoint.position = Vector3(-122.81f, -1.0f, -23.0f);
        waypoint.rotation = Vector3(30.0f, 00.0f, -70.0f);
        seqTieTwoEnd.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-99.6f, -10.0f, -66.0f);
        waypoint.rotation = Vector3(30.0f, 0.0f, -85.0f);
        seqTieTwoEnd.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqTieTwoEnd);




        // ==================================== =Seq tie three

        Sequence seqTieThree;
        seqTieThree.name = "TieTwoStart";
        seqTieThree.startTime = 10.0f;
        seqTieThree.duration = 4.0f;
        seqTieThree.objectTransform = tieThreeTransform;
        seqTieThree.curve = true;
        seqTieThree.play = false;
        waypoint.position = Vector3(-118.24f, 10.0f, 25.32f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 50.0f);
        seqTieThree.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-146.78f, 0.0f, 0.62f);
        waypoint.rotation = Vector3(20.0f, 0.0f, 60.0f);
        seqTieThree.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-157.44f, -6.0f, -4.9f);
        waypoint.rotation = Vector3(-10.0f, 0.0f, -40.0f);
        seqTieThree.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-122.81f, -1.0f, -22.0f);
        waypoint.rotation = Vector3(30.0f, 0.0f, -70.0f);
        seqTieThree.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqTieThree);


        Sequence seqTieThreeEnd;
        seqTieThreeEnd.name = "TieTwoEnd";
        seqTieThreeEnd.startTime = 14.00f;
        seqTieThreeEnd.duration = 2.0f;
        seqTieThreeEnd.objectTransform = tieThreeTransform;
        seqTieThreeEnd.curve = false;
        seqTieThreeEnd.play = false;
        waypoint.position = Vector3(-122.81f, -1.0f, -22.0f);
        waypoint.rotation = Vector3(30.0f, 00.0f, -70.0f);
        seqTieThreeEnd.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-82.6f, 17.0f, -44.0f);
        waypoint.rotation = Vector3(30.0f, 0.0f, -85.0f);
        seqTieThreeEnd.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqTieThreeEnd);



        // Seq TIE FOUR ========================================================
        Sequence seqTieFour;
        seqTieFour.name = "TieTwoStart";
        seqTieFour.startTime = 10.0f;
        seqTieFour.duration = 4.0f;
        seqTieFour.objectTransform = tieFourTransform;
        seqTieFour.curve = true;
        seqTieFour.play = false;
        waypoint.position = Vector3(-121.24f, 10.0f, 26.32f);
        waypoint.rotation = Vector3(0.0f, 0.0f, -50.0f);
        seqTieFour.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-136.78f, 43.0f, 3.62f);
        waypoint.rotation = Vector3(-20.0f, 0.0f, -60.0f);
        seqTieFour.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-138.44f, 19.0f, 7.9f);
        waypoint.rotation = Vector3(10.0f, 0.0f, 40.0f);
        seqTieFour.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-123.81f, 9.0f, -22.0f);
        waypoint.rotation = Vector3(30.0f, 0.0f, 70.0f);
        seqTieFour.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqTieFour);


        Sequence seqTieFourEnd;
        seqTieFourEnd.name = "TieTwoEnd";
        seqTieFourEnd.startTime = 14.00f;
        seqTieFourEnd.duration = 2.0f;
        seqTieFourEnd.objectTransform = tieFourTransform;
        seqTieFourEnd.curve = false;
        seqTieFourEnd.play = false;
        waypoint.position = Vector3(-123.81f, 9.0f, -22.0f);
        waypoint.rotation = Vector3(-30.0f, 00.0f, 70.0f);
        seqTieFourEnd.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-98.6f, 0.0f, -66.0f);
        waypoint.rotation = Vector3(-30.0f, 0.0f, 85.0f);
        seqTieFourEnd.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqTieFourEnd);

     
    }


    void SetUpSequenceThree()
    {

        Entity blastEntity = GetCurrentScene()->CreateEntity("Blast");
        blastTransform = &blastEntity.AddComponent<Transform>();
        // asteroidtransform->SetPosition(Vector3(1.2f, 5.0f, -9.5f));
        blastTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
        blastTransform->SetEularRotation(Vector3(00.0f, 0.0f, 00.0f));
        blastTransform->SetScale(Vector3(0.0f));


        SharedPtr<Mesh>mesh = GetModelLibrary()->GetResource("Blast")->GetMeshes()[0];
        blastEntity.AddComponent<MeshComponent>(mesh);

        SharedPtr<Material> albedoMat = blastEntity.AddComponent<MeshRenderer>().GetMaterial();
        albedoMat->textureMaps.albedoMap = GetTextureLibrary()->GetResource("BlastAlbedo");
        albedoMat->type = MaterialType::Opaque;
        albedoMat->roughness = 0.0f;









        Waypoint waypoint;


        Sequence seqThreeCamera;

        seqThreeCamera.name = "FalconFlyCamera";
        seqThreeCamera.startTime = 15.0f;
        seqThreeCamera.duration = 6.0f;
        seqThreeCamera.objectTransform = mainCameraTransform;
        seqThreeCamera.curve = false;
        seqThreeCamera.play = false;
        waypoint.position = Vector3(0.34f, 6.51f, -13.0f);
        waypoint.rotation = Vector3(-178.31f, 2.3f, 178.2);
        seqThreeCamera.waypointList.push_back(waypoint);
        waypoint.position = Vector3 (0.34f, 6.51f, -13.0f);
        waypoint.rotation = Vector3(-178.31f, 2.31f, 178.2);
        seqThreeCamera.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqThreeCamera);



        Sequence seqFillerAsteroindOne;
        seqFillerAsteroindOne.name = "FillerOne";
        seqFillerAsteroindOne.startTime = 14.9f;
        seqFillerAsteroindOne.duration = 5.0f;
        seqFillerAsteroindOne.objectTransform = filleTwoTransform;
        seqFillerAsteroindOne.curve = false;
        seqFillerAsteroindOne.play = false;
        waypoint.position = Vector3(23.0f, -8.0f, 50.6f);
        waypoint.rotation = Vector3(30.0f, 60.0f, 0.0f);
        seqFillerAsteroindOne.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-12.0f, -8.0f, 5.6f);
        waypoint.rotation = Vector3(-30.0f, 0.0f, 0.0f);
        seqFillerAsteroindOne.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqFillerAsteroindOne);



        Sequence seqDirectionalLight;

        seqDirectionalLight.name = "Directional";
        seqDirectionalLight.startTime = 14.9f;
        seqDirectionalLight.duration = 0.1f;
        seqDirectionalLight.objectTransform = directionLightTransform;
        seqDirectionalLight.curve = false;
        seqDirectionalLight.play = false;

        waypoint.position = Vector3(-29.0f, 6.0f, -1.6f);
        waypoint.rotation = Vector3(-171.0f, -78.27f, 174.0f);
        seqDirectionalLight.waypointList.push_back(waypoint);

        waypoint.position = Vector3(-29.0f, 6.0f, -1.6f);
        waypoint.rotation = Vector3(179.0f, -5.27f, 178.0);
        seqDirectionalLight.waypointList.push_back(waypoint);

        sequencer->AddSequence(seqDirectionalLight);


        // Colliding asteroid



        Sequence seqAsteroidRotate;
        seqAsteroidRotate.name = "Asteroidrotate";
        seqAsteroidRotate.startTime = 15.0f;
        seqAsteroidRotate.duration = 5.6f;
        seqAsteroidRotate.objectTransform = filleOneTransform;
        seqAsteroidRotate.curve = false;
        seqAsteroidRotate.play = false;

        waypoint.position = Vector3(30.2f, 62.0f, 29.5f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqAsteroidRotate.waypointList.push_back(waypoint);

        waypoint.position = Vector3(-14.0f, -20.0f, 0.0f);
        waypoint.rotation = Vector3(0.0f, 10.0f, 80.0f);
        seqAsteroidRotate.waypointList.push_back(waypoint);


        sequencer->AddSequence(seqAsteroidRotate);

        //Tie one Sequence

        Sequence seqTieOne;
        seqTieOne.name = "FalconDodgeTwo";
        seqTieOne.startTime = 14.8f;
        seqTieOne.duration = 3.0f;
        seqTieOne.objectTransform = tieOneTransform;
        seqTieOne.curve = true;
        seqTieOne.play = false;
        waypoint.position = Vector3(-10.24f, 15.0f, 20.32f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieOne.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-8.78f, 1.0f, 19.62f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieOne.waypointList.push_back(waypoint);
        waypoint.position = Vector3(8.6f, 1.0f, 2.2f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieOne.waypointList.push_back(waypoint);
        waypoint.position = Vector3(40.81f, -2.0f, -12.0f);
        waypoint.rotation = Vector3(0.0f, 40.0f, 0.0f);
        seqTieOne.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqTieOne);




        // Tie Two sequence


        Sequence seqTieTwo;
        seqTieTwo.name = "TieTwoStart";
        seqTieTwo.startTime = 15.0f;
        seqTieTwo.duration = 3.0f;
        seqTieTwo.objectTransform = tieTwoTransform;
        seqTieTwo.curve = true;
        seqTieTwo.play = false;
        waypoint.position = Vector3(0.0f, 25.0f, 20.97f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieTwo.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-2.30f, 1.0f, 19.6f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieTwo.waypointList.push_back(waypoint);
        waypoint.position = Vector3(3.60f, 0.0f, 2.2f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieTwo.waypointList.push_back(waypoint);
        waypoint.position = Vector3(7.0f, 0.0f, -19.0f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieTwo.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqTieTwo);



        // Seq Tie Three

        Sequence seqTieThree;
        seqTieThree.name = "TieThreeStart";
        seqTieThree.startTime = 16.0f;
        seqTieThree.duration = 2.3f;
        seqTieThree.objectTransform = tieThreeTransform;
        seqTieThree.curve = true;
        seqTieThree.play = false;
        waypoint.position = Vector3(5.5f, 30.0f, 30.32f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieThree.waypointList.push_back(waypoint);
        waypoint.position = Vector3(3.18f, 1.5f, 19.62f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieThree.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-1.13f, 8.0f, 14.9f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieThree.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-0.49f, 8.0f, 10.0f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieThree.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqTieThree);


        Sequence seqTieThreeEnd;
        seqTieThreeEnd.name = "TieThreeStart";
        seqTieThreeEnd.startTime = 18.4f;
        seqTieThreeEnd.duration = 0.2f;
        seqTieThreeEnd.objectTransform = tieThreeTransform;
        seqTieThreeEnd.curve = true;
        seqTieThreeEnd.play = false;
        waypoint.position = Vector3(0.f, -5000.0f, 0.0f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieThreeEnd.waypointList.push_back(waypoint);
        waypoint.position = Vector3(0.f, -5000.0f, 0.0f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieThreeEnd.waypointList.push_back(waypoint);
 
        sequencer->AddSequence(seqTieThreeEnd);


        // Tie Four Start

        Sequence seqTieFour;
        seqTieFour.name = "TieFourStart";
        seqTieFour.startTime = 15.0f;
        seqTieFour.duration = 3.0f;
        seqTieFour.objectTransform = tieFourTransform;
        seqTieFour.curve = true;
        seqTieFour.play = false;
        waypoint.position = Vector3(-16.0f, 20.0f, 20.97f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieFour.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-18.30f, 4.0f, 19.6f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieFour.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-9.1f, 8.0f, -7.2f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieFour.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-8.0f, 7.0f, -11.0f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqTieFour.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqTieFour);

        // ====================== BLAST SEQ =================================
        Sequence seqBlast;
        seqBlast.name = "BlastSeq";
        seqBlast.startTime = 18.3f;
        seqBlast.duration = 0.7f;
        seqBlast.objectTransform = blastTransform;
        seqBlast.curve = false;
        seqBlast.play = false;
        seqBlast.changeScale = true;
        waypoint.position = Vector3(0.35f, 9.55f, 15.0f);
        waypoint.rotation = Vector3(-90.0f, 0.0f, 0.0f);
        waypoint.scale = Vector3(0.0f);
        seqBlast.waypointList.push_back(waypoint);
        waypoint.position = Vector3(0.35f, 9.55f, 15.0f);
        waypoint.rotation = Vector3(-90.0f, 00.0f, 030.0f);
        waypoint.scale = Vector3(7.0f);

        seqBlast.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqBlast);

        Sequence seqBlastEnd;
        seqBlastEnd.name = "BlastSeq";
        seqBlastEnd.startTime = 19.0f;
        seqBlastEnd.duration = 0.55f;
        seqBlastEnd.objectTransform = blastTransform;
        seqBlastEnd.curve = false;
        seqBlastEnd.play = false;
        seqBlastEnd.changeScale = true;
        waypoint.position = Vector3(0.35f, 9.55f, 15.0f);
        waypoint.rotation = Vector3(-90.0f, 0.0f, 0.0f);
        waypoint.scale = Vector3(7.0f);
        seqBlastEnd.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-0.35f, 9.55f, 15.0f);
        waypoint.rotation = Vector3(-90.0f, 00.0f, 030.0f);
        waypoint.scale = Vector3(0.0f);

        seqBlastEnd.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqBlastEnd);

        Sequence seqBlastClean;
        seqBlastClean.name = "BlastSeqClean";
        seqBlastClean.startTime = 19.0f;
        seqBlastClean.duration = 0.55f;
        seqBlastClean.objectTransform = blastTransform;
        seqBlastClean.curve = false;
        seqBlastClean.play = false;
        waypoint.position = Vector3(0.0f, 5000.0f, .0f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqBlastClean.waypointList.push_back(waypoint);
        waypoint.position = Vector3(0.0f, 85000.0f, 00.0f);
        waypoint.rotation = Vector3((0.0f, 0.0f, 0.0f));
        seqBlastClean.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqBlastClean);




    }


    void SetUpSequenceFour()
    {
        Waypoint waypoint;

        Sequence seqAsteroidRotate;
        seqAsteroidRotate.name = "Asteroidrotate";
        seqAsteroidRotate.startTime = 20.0f;
        seqAsteroidRotate.duration = 10.6f;
        seqAsteroidRotate.objectTransform = filleOneTransform;
        seqAsteroidRotate.curve = false;
        seqAsteroidRotate.play = false;

        waypoint.position = Vector3(-3.15f, 6.00f, 5.90f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqAsteroidRotate.waypointList.push_back(waypoint);

        waypoint.position = Vector3(-3.15f, 15.00f, 15.0f);
        waypoint.rotation = Vector3(0.0f, 10.0f, 80.0f);
        seqAsteroidRotate.waypointList.push_back(waypoint);


        sequencer->AddSequence(seqAsteroidRotate);





        // Falcon Sequence


        Sequence seqDodge;
        seqDodge.name = "FalconGobetweenrocks";
        seqDodge.startTime= 20.00f;
        seqDodge.duration = 4.0f;
        seqDodge.objectTransform = falconTransform;
        seqDodge.curve = true;
        seqDodge.play = false;
        seqDodge.changeScale = true;
        waypoint.position = Vector3(-2.4f, 3.0f, 42.32f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 50.0f);
        waypoint.scale = Vector3(0.02f, 0.02f, 0.02f);
        seqDodge.waypointList.push_back(waypoint);
        waypoint.position = Vector3(15.78f, -1.0f, 6.62f);
        waypoint.rotation = Vector3(-20.0f, 0.0f, 80.0f);
        waypoint.scale = Vector3(0.02f, 0.02f, 0.02f);
        seqDodge.waypointList.push_back(waypoint);
        waypoint.position = Vector3(2.6f, 11.0f, 8.5f);
        waypoint.rotation = Vector3(10.0f, 0.0f, 70.0f);
        waypoint.scale = Vector3(0.02f, 0.02f, 0.02f);
        seqDodge.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-5.81f, 9.0f, -11.0f);
        waypoint.rotation = Vector3(5.0f, 0.0f, -20.0f);
        waypoint.scale = Vector3(0.02f, 0.02f, 0.02f);
        seqDodge.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqDodge);



        Sequence seqDirectionalLight;

        seqDirectionalLight.name = "Directional";
        seqDirectionalLight.startTime = 19.9f;
        seqDirectionalLight.duration = 0.5f;
        seqDirectionalLight.objectTransform = directionLightTransform;
        seqDirectionalLight.curve = false;
        seqDirectionalLight.play = false;

        waypoint.position = Vector3(-29.0f, 6.0f, -1.6f);
        waypoint.rotation = Vector3(-178.0f,31.0f, 177.0f);
        seqDirectionalLight.waypointList.push_back(waypoint);

        waypoint.position = Vector3(-29.0f, 6.0f, -1.6f);
        waypoint.rotation = Vector3(-178.0f, 33.0f, 177.0f);
        seqDirectionalLight.waypointList.push_back(waypoint);

        sequencer->AddSequence(seqDirectionalLight);


        Sequence seqAsteroid;
        seqAsteroid.name = "Asteroidrotate";
        seqAsteroid.startTime = 20.0f;
        seqAsteroid.duration = 3.6f;
        seqAsteroid.objectTransform = filleTwoTransform;
        seqAsteroid.curve = true;
        seqAsteroid.play = false;

        waypoint.position = Vector3(19.33f, 6.66f, 20.90f);
        waypoint.rotation = Vector3(0.0f, 0.0f, -20.0f);
        seqAsteroid.waypointList.push_back(waypoint);

        waypoint.position = Vector3(15.33f, -1.66f, 18.90f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqAsteroid.waypointList.push_back(waypoint);

        waypoint.position = Vector3(11.0f, -7.00f, 12.0f);
        waypoint.rotation = Vector3(0.0f, 10.0f, 60.0f);
        seqAsteroid.waypointList.push_back(waypoint);

        waypoint.position = Vector3(6.33f, 31.66f, 11.90f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 90.0f);
        seqAsteroid.waypointList.push_back(waypoint);
      

        sequencer->AddSequence(seqAsteroid);




        Sequence seqTieThreeEnd;
        seqTieThreeEnd.name = "TieThreeEnd";
        seqTieThreeEnd.startTime = 23.00f;
        seqTieThreeEnd.duration = 2.5f;
        seqTieThreeEnd.objectTransform = tieThreeTransform;
        seqTieThreeEnd.curve = false;
        seqTieThreeEnd.changeScale = true;
        seqTieThreeEnd.play = false;
        waypoint.position = Vector3(26.81f, -4.0f, 38.0f);
        waypoint.rotation = Vector3(14.0f, 14.0f, 1.8f);
        waypoint.scale = Vector3(0.0f);
        seqTieThreeEnd.waypointList.push_back(waypoint);
        waypoint.position = Vector3(-14.6f, 4.0f, -20.0f);
        waypoint.rotation = Vector3(14.0f, 14.0f, 1.8f);
        waypoint.scale = Vector3(0.3f);
        seqTieThreeEnd.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqTieThreeEnd);



        Sequence seqTieTwoEnd;
        seqTieTwoEnd.name = "TieThreeEnd";
        seqTieTwoEnd.startTime = 23.00f;
        seqTieTwoEnd.duration = 2.0f;
        seqTieTwoEnd.objectTransform = tieTwoTransform;
        seqTieTwoEnd.curve = false;
        seqTieTwoEnd.changeScale = true;
        seqTieTwoEnd.play = false;
        waypoint.position = Vector3(30.81f, 4.0f, 38.0f);
        waypoint.rotation = Vector3(5.0f, 20.0f, 1.8f);
        waypoint.scale = Vector3(0.0f);
        seqTieTwoEnd.waypointList.push_back(waypoint);
        waypoint.position = Vector3(8.6f, 8.0f, 10.0f);
        waypoint.rotation = Vector3(5.0f, 20.0f, 1.8f);
        waypoint.scale = Vector3(0.3f);
        seqTieTwoEnd.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqTieTwoEnd);



        Sequence seqTieTwoBlast;
        seqTieTwoBlast.name = "TieThreeEnd";
        seqTieTwoBlast.startTime = 25.2f;
        seqTieTwoBlast.duration = 2.5f;
        seqTieTwoBlast.objectTransform = tieTwoTransform;
        seqTieTwoBlast.curve = true;
        seqTieTwoBlast.play = false;
        seqTieTwoEnd.changeScale = true;
        waypoint.position = Vector3(8.6f, 8.0f, 10.0f);
        waypoint.rotation = Vector3(20.0f, 0.0f, 20.0f);
        waypoint.scale = Vector3(0.3f);
        seqTieTwoBlast.waypointList.push_back(waypoint);
        waypoint.position = Vector3(14.6f, 6.0f, 1.0f);
        waypoint.rotation = Vector3(0.0f, 00.0f, -00.0f);
        waypoint.scale = Vector3(0.3f);
        seqTieTwoBlast.waypointList.push_back(waypoint);
      
        waypoint.position = Vector3(14.6f, 18.0f, 18.0f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        waypoint.scale = Vector3(0.3f);
        seqTieTwoBlast.waypointList.push_back(waypoint);

        waypoint.position = Vector3(-1.6f, 10.0f, -25.0f);
        waypoint.rotation = Vector3(45.0f, 5.0f, 80.0f);
        waypoint.scale = Vector3(0.3f);
        seqTieTwoEnd.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqTieTwoBlast);




        Sequence seqFourCamera;

        seqFourCamera.name = "FalconFlyCamera";
        seqFourCamera.startTime = 25.0f;
        seqFourCamera.duration = 3.0f;
        seqFourCamera.objectTransform = mainCameraTransform;
        seqFourCamera.curve = false;
        seqFourCamera.play = false;
        waypoint.position = Vector3(0.34f, 6.51f, -13.0f);
        waypoint.rotation = Vector3(-178.31f, 2.3f, 178.2);
        seqFourCamera.waypointList.push_back(waypoint);
        waypoint.position = Vector3(0.34f, 6.51f, -6.0f);
        waypoint.rotation = Vector3(-178.31f, 2.31f, 178.2);
        seqFourCamera.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqFourCamera);


        Sequence seqAsteroidEnd;
        seqAsteroidEnd.name = "Asteroidrotate";
        seqAsteroidEnd.startTime = 23.0f;
        seqAsteroidEnd.duration = 2.0f;
        seqAsteroidEnd.objectTransform = BigAsteroidOneTransform;
        seqAsteroidEnd.curve = false;
        seqAsteroidEnd.play = false;
        seqAsteroidEnd.changeScale = true;
        waypoint.position = Vector3(30.0f,-9.0f, -13.5f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        waypoint.rotation = Vector3(0.05f);
        seqAsteroidEnd.waypointList.push_back(waypoint);

        waypoint.position = Vector3(8.6f, 8.0f, 10.0f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        waypoint.rotation = Vector3(0.05f);
        seqAsteroidEnd.waypointList.push_back(waypoint);

        sequencer->AddSequence(seqAsteroidEnd);




        Sequence seqAsteroidBlast;
        seqAsteroidBlast.name = "Asteroidrotate";
        seqAsteroidBlast.startTime = 25.1f;
        seqAsteroidBlast.duration = 0.5f;
        seqAsteroidBlast.objectTransform = BigAsteroidOneTransform;
        seqAsteroidBlast.curve = false;
        seqAsteroidBlast.play = false;
        seqAsteroidBlast.changeScale = true;
        waypoint.position = Vector3(30.0f,5000.0f, -13.5f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        waypoint.rotation = Vector3(0.05f);
        seqAsteroidBlast.waypointList.push_back(waypoint);

        waypoint.position = Vector3(8.6f, 50000.0f, 10.0f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        waypoint.rotation = Vector3(0.01f);
        seqAsteroidBlast.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqAsteroidBlast);



         Sequence seqBlast;
        seqBlast.name = "BlastSeq";
        seqBlast.startTime = 25.0f;
        seqBlast.duration = 0.7f;
        seqBlast.objectTransform = blastTransform;
        seqBlast.curve = false;
        seqBlast.play = false;
        seqBlast.changeScale = true;
        waypoint.position = Vector3(8.6f, 8.0f, 9.2f);
        waypoint.rotation = Vector3(-90.0f, 0.0f, 0.0f);
        waypoint.scale = Vector3(0.0f);
        seqBlast.waypointList.push_back(waypoint);
        waypoint.position = Vector3(8.6f, 8.0f, 9.2f);
        waypoint.rotation = Vector3(-90.0f, 00.0f, 030.0f);
        waypoint.scale = Vector3(3.0f);

        seqBlast.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqBlast);

        Sequence seqBlastEnd;
        seqBlastEnd.name = "BlastSeqEnd";
        seqBlastEnd.startTime = 25.8f;
        seqBlastEnd.duration = 0.55f;
        seqBlastEnd.objectTransform = blastTransform;
        seqBlastEnd.curve = false;
        seqBlastEnd.play = false;
        seqBlastEnd.changeScale = true;
        waypoint.position = Vector3(8.6f, 8.0f, 9.2f);
        waypoint.rotation = Vector3(-90.0f, 0.0f, 0.0f);
        waypoint.scale = Vector3(3.0f);
        seqBlastEnd.waypointList.push_back(waypoint);
        waypoint.position = Vector3(8.6f, 8.0f, 9.2f);
        waypoint.rotation = Vector3(-90.0f, 00.0f, 030.0f);
        waypoint.scale = Vector3(0.0f);

        seqBlastEnd.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqBlastEnd);

        Sequence seqBlastClean;
        seqBlastClean.name = "BlastSeqClean";
        seqBlastClean.startTime = 26.0f;
        seqBlastClean.duration = 0.55f;
        seqBlastClean.objectTransform = blastTransform;
        seqBlastClean.curve = false;
        seqBlastClean.play = false;
        waypoint.position = Vector3(0.0f, 5000.0f, .0f);
        waypoint.rotation = Vector3(0.0f, 0.0f, 0.0f);
        seqBlastClean.waypointList.push_back(waypoint);
        waypoint.position = Vector3(0.0f, 5000.0f, 00.0f);
        waypoint.rotation = Vector3((0.0f, 0.0f, 0.0f));
        seqBlastClean.waypointList.push_back(waypoint);
        sequencer->AddSequence(seqBlastClean);


    }



    SharedPtr<Sequencer> sequencer;
    bool playSequencer;
    Transform* mainCameraTransform = nullptr;
    Transform* falconTransform = nullptr;
    Transform* tieOneTransform = nullptr;
    Transform* tieTwoTransform = nullptr;
    Transform* tieThreeTransform = nullptr;
    Transform* tieFourTransform = nullptr;

    Transform* blastTransform;

    Transform* BigAsteroidOneTransform = nullptr;
    Transform* filleOneTransform = nullptr;
    Transform* filleTwoTransform = nullptr;


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