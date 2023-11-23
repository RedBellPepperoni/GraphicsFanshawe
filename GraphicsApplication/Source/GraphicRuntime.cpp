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


        AddAudio("Assets\\Audio\\EnchantedFestival.mp3", Vector3(1.0f));


        playerTransform = GetCurrent().GetCurrentScene()->GetMainCameraTransform();

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


        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("Sphere")->GetMeshes()[0];
        //SharedPtr<Mesh> mesh = modelLibrary->GetResource("Ground")->GetMeshes()[0];

        audioEntity.AddComponent<MeshComponent>(mesh);
        SharedPtr<Material> material = audioEntity.AddComponent<MeshRenderer>().GetMaterial();

      
       

    }

    void OnUpdate(float deltaTime)
    {
        // Input map for switching between the Wireframe and normal displays
        if (Input::InputSystem::GetInstance().GetKeyDown(Input::Key::G))
        {
            GetCurrent().GetAppWindow()->ToggleWireframe();
        }

       

        Audio::AudioManager::GetInstance().SetListenerAttributes(playerTransform->GetPosition(), Vector3(0.0f), playerTransform->GetRotation() * Vector3(0.0f,0.0f,1.0f), Vector3(0.0f, 1.0f, 0.0f));
        Audio::AudioManager::GetInstance().GetListernerAttributes();

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