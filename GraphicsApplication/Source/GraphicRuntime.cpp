#pragma once
#include "GameEngine.h"
#include "SceneParser.h"
#include "SceneLoader.h"


class GraphicProject : public Application
{
    void OnInit()
    {
        parser = Factory<SceneParser>::Create();
        loader = Factory<SceneLoader>::Create();

        // parse the scene with the name
        parser->ParseScene("Engine\\Scene\\SceneSubway.json");

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



        



        AddAudio("Assets\\Audio\\EnchantedFestival.mp3", Vector3(-1.2f,1.0f,-1.0));


        playerTransform = GetCurrent().GetCurrentScene()->GetMainCameraTransform();



        Entity audioOccluder = m_currentScene->CreateEntity("AudioOccluder");

        Transform* transform = &audioOccluder.AddComponent<Transform>();
        transform->SetPosition(Vector3(3.0f, 2.0f, 0.0f));

        AudioManager::GetInstance().CreateGeometry(audioOccluder);

        SharedPtr<Mesh> audioMesh = GetModelLibrary()->GetResource("Sphere")->GetMeshes()[0];


        audioOccluder.AddComponent<MeshComponent>(audioMesh);
        audioOccluder.AddComponent<MeshRenderer>();

    }


    void AddAudio(const std::string& filePath, const Vector3& position)
    {
        Entity audioEntity = m_currentScene->CreateEntity("AudioSource");

        Transform* transform = &audioEntity.AddComponent<Transform>();

        transform->SetPosition(position);

        Audio::AudioSource* source = &audioEntity.AddComponent<Audio::AudioSource>(transform);


        

        SharedPtr<AudioClip> clip = GetCurrent().GetAudioLibrary()->LoadAudio("RadioMusic",filePath);
   

        if (clip != nullptr)
        {
            source->SetAudioClip(clip);
            source->PlayClip();
        }
 

    }


    void AddWall(const Vector3& position, const Vector3 rotation)
    {
        Entity wallEntity = m_currentScene->CreateEntity("Wall");
        Transform* transform = &wallEntity.AddComponent<Transform>();

        transform->SetPosition(position);
        transform->SetRotation(rotation);

       // wallEntity.AddComponent<>
    }


    void OnUpdate(float deltaTime)
    {
        // Input map for switching between the Wireframe and normal displays
        if (Input::InputSystem::GetInstance().GetKeyDown(Input::Key::G))
        {
            GetCurrent().GetAppWindow()->ToggleWireframe();
        }

       

       // Audio::AudioManager::GetInstance().SetListenerAttributes(playerTransform->GetPosition(), Vector3(0.0f), playerTransform->GetRotation() * Vector3(0.0f,0.0f,1.0f), Vector3(0.0f, 1.0f, 0.0f));
       // Audio::AudioManager::GetInstance().GetListernerAttributes();


      


        Audio::AudioManager::GetInstance().Update();

    }


   

    



private:

    SharedPtr<SceneParser> parser = nullptr;
    SharedPtr<SceneLoader> loader = nullptr;

    Transform* playerTransform = nullptr;
};


int main(int argc, char* argv)
{
    // Creating a new Appinstance
    GraphicProject* app = new GraphicProject();

    //FilePath path = File::GetCurrentPath();

    // Always Initialize the App
    app->Initialize();
    // Running the Application
    app->Run();


    delete app;
}