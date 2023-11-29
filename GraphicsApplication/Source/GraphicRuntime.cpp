#pragma once
#include "GameEngine.h"
#include "SceneParser.h"
#include "SceneLoader.h"
#include "Editor/GUI/AudioEditor.h"


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


        //Trees
        AddOccluder(Vector3(3.9f, 3.0f, -2.0f),Vector3(0.0f, 70.0f,0.0f), Vector2(1.6,6));
        AddOccluder(Vector3(-2.5f, 3.0f, -3.6f), Vector3(0.0f, -30.0f, 0.0f), Vector2(1.6, 6));
        AddOccluder(Vector3(-0.9f, 3.0f, 2.3f), Vector3(0.0f, 0.0f, 0.0f), Vector2(2, 6));
        AddOccluder(Vector3(-2.9f, 3.0f, 3.9f), Vector3(0.0f, -30.0f, 0.0f), Vector2(2, 6));
        AddOccluder(Vector3(0.4f, 3.0f, 5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(2, 6));


        // Rock Big
        AddOccluder(Vector3(4.4f, 0.5f, -1.2f),Vector3(0.0f, 70.0f,0.0f), Vector2(3,1));
        
        //AddOccluder(Vector3(4.4f, 0.5f, -1.2f),Vector3(0.0f), Vector2(3,1));



        AudioSource* source =  AddAudio("RadioMusic","Assets\\Audio\\EnchantedFestival.mp3", Vector3(-0.04f,1.53f,-0.4f));


        source->PlayClip();
        source->Set3DMinDist(1.0f);
        source->Set3DMaxDist(10.0f);

        source->AddDSPEffect(Audio::DSPEffects::REVERB);
        source->AddDSPEffect(Audio::DSPEffects::DISTORTION);
        source->AddDSPEffect(Audio::DSPEffects::LOWPASS);
        source->AddDSPEffect(Audio::DSPEffects::HIGHPASS);
        source->AddDSPEffect(Audio::DSPEffects::ECHO);


        int index= source->GetChannelIndex();

        source = AddAudio("Fire", "Assets\\Audio\\Fire.mp3", Vector3(0.8f, 1.0f, 1.2f));

        source->PlayClip();
        source->Set3DMinDist(1.0f);
        source->Set3DMaxDist(5.0f);

        

        playerTransform = GetCurrent().GetCurrentScene()->GetMainCameraTransform();



        //AddDirLight(Vector3(0.0f,0.0f,0.0f), Vector3(-30.0f,10.0f,0.0f), Vector3(1.0f,1.0f,0.0f), 0.4f);
        AddPointLight(Vector3(0.8f, 1.0f, 1.2f), Vector3(1.0f, 0.0f, 0.0f), 1.7f, 2.0f);

    }


    AudioSource*  AddAudio(const std::string& name ,const std::string& filePath, const Vector3& position)
    {
        Entity audioEntity = m_currentScene->CreateEntity("AudioSource");

        Transform* transform = &audioEntity.AddComponent<Transform>();

        transform->SetPosition(position);

        Audio::AudioSource* source = AudioManager::GetInstance().CreateSource(audioEntity);


        SharedPtr<AudioClip> clip = GetCurrent().GetAudioLibrary()->LoadAudio(name,filePath);
        

        if (clip != nullptr)
        {
            source->SetAudioClip(clip);
            source->SetLoop(true);
            
        }
 
        return source;

    }


    void AddOccluder(const Vector3& position, const Vector3 rotation, const Vector2& dimentions)
    {

        Entity audioOccluder = m_currentScene->CreateEntity("AudioOccluder");

        Transform* transform = &audioOccluder.AddComponent<Transform>();

        transform->SetPosition(position);
        transform->SetRotation(rotation);


        Audio::AudioGeometry* geo = AudioManager::GetInstance().CreateGeometry(audioOccluder);

        AudioManager::GetInstance().AddOcclusionPolygon(geo, transform, dimentions);

       // wallEntity.AddComponent<>
    }

    void AddDirLight(const Vector3& position, const Vector3& rotation,const Vector3& color, const float intensity)
    {
        Entity dirLight = m_currentScene->CreateEntity("DirectionalLight");

        Transform& transform = dirLight.AddComponent<Transform>();
        transform.SetPosition(position);
        transform.SetRotation(rotation);

        Light& light = dirLight.AddComponent<Light>();
        light.type = LightType::DirectionLight;
        light.intensity = intensity < 0.0f ? 0.0f : intensity;

    }

    void AddPointLight(const Vector3& position,const Vector3& color, const float intensity, const float radius)
    {
        Entity dirLight = m_currentScene->CreateEntity("DirectionalLight");

        Transform& transform = dirLight.AddComponent<Transform>();
        transform.SetPosition(position);
        transform.SetRotation(Vector3(0.0f));

        Light& light = dirLight.AddComponent<Light>();
        light.type = LightType::PointLight;
        light.intensity = intensity <= 0.0f ? 0.0f : intensity;

        light.radius = radius <= 0.0f ? 0.0f : radius;

    }


    void OnUpdate(float deltaTime)
    {
        // Input map for switching between the Wireframe and normal displays
        if (Input::InputSystem::GetInstance().GetKeyDown(Input::Key::G))
        {
            GetCurrent().GetAppWindow()->ToggleWireframe();
        }


        Audio::AudioManager::GetInstance().Update(deltaTime);

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