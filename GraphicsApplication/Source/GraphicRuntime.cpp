#pragma once
#include "GameEngine.h"
#include "SceneParser.h"
#include "SceneLoader.h"
#include "Editor/GUI/AudioEditor.h"
#include "Editor/GUI/RuntimeEditor.h"
#include "Engine/Core/Rendering/Renderer/DebugRenderer.h"

class GraphicProject : public Application
{
    void OnInit()
    {
        parser = Factory<SceneParser>::Create();
        loader = Factory<SceneLoader>::Create();

        // parse the scene with the name
        parser->ParseScene("Engine\\Scene\\SceneRoute66.json");

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

       
        playerTransform = GetCurrent().GetCurrentScene()->GetMainCameraTransform();

        // Directional
        dayData.emplace_back(1.0f, Vector3(1.0f, 1.0f, 0.99f));
        //Logo POint Lights
        dayData.emplace_back(0.01f, Vector3(1.0f, 0.2f, 0.1f));
        dayData.emplace_back(0.01f, Vector3(1.0f, 0.2f, 0.1f));
        dayData.emplace_back(0.01f, Vector3(1.0f, 0.2f, 0.1f));

        // Spots

        dayData.emplace_back(0.01f, Vector3(1.0f, 1.0f, 0.4f));
        dayData.emplace_back(0.01f, Vector3(1.0f, 1.0f, 0.4f));
        dayData.emplace_back(0.01f, Vector3(1.0f, 1.0f, 0.4f));
        dayData.emplace_back(0.01f, Vector3(1.0f, 1.0f, 0.4f));
        dayData.emplace_back(0.01f, Vector3(1.0f, 1.0f, 0.4f));
        dayData.emplace_back(0.01f, Vector3(1.0f, 1.0f, 0.4f));

        nightData.emplace_back(0.08f, Vector3(0.0f, 0.0f, 1.00f));
        //Logo POint Lights
        nightData.emplace_back(3.2f, Vector3(1.0f, 0.3f, 0.3f));
        nightData.emplace_back(3.2f, Vector3(1.0f, 0.3f, 0.3f));
        nightData.emplace_back(2.2f, Vector3(1.0f, 1.0f, 0.8f));

        // Spots

        nightData.emplace_back(2.0f, Vector3(1.0f, 1.0f, 0.4f));
        nightData.emplace_back(1.1f, Vector3(1.0f, 1.0f, 0.4f));
        nightData.emplace_back(2.1f, Vector3(1.0f, 1.0f, 0.4f));
        nightData.emplace_back(2.1f, Vector3(1.0f, 1.0f, 0.4f));
        nightData.emplace_back(1.1f, Vector3(1.0f, 1.0f, 0.4f));
        nightData.emplace_back(3.81f, Vector3(1.0f, 1.0f, 0.4f));


        AddDirLight(Vector3(0.0f,0.0f,0.0f), Vector3(-45.0f,-43.0f,0.0f), Vector3(1.0f,1.0f,0.99f), 1.0f);
        AddPointLight(Vector3(0.69f, 6.29f, 5.08f), Vector3(1.0f, 0.3f, 0.3f), 0.01f, 3.0f);
        AddPointLight(Vector3(-1.96f, 6.29f, 5.08f), Vector3(1.0f, 0.3f, 0.3f), 0.01f, 3.0f);
        AddPointLight(Vector3(-1.96f, 3.29f, 5.08f), Vector3(1.0f, 1.0f, 0.8f), 0.01f, 3.0f);


        AddSpotLight(Vector3(-0.36f, 2.8f, 1.67f), Vector3(0.0f, -1.0f, 0.0f), Vector3(1.0f, 1.0f, 0.4f), 0.01f, 30.0f, 70.0f);
        AddSpotLight(Vector3(-1.86f,2.5f,-2.36f), Vector3(0.0f, -1.0f, 0.0f), Vector3(1.0f, 1.0f, 0.4f), 0.01f, 30.0f, 70.0f);
        AddSpotLight(Vector3(-0.35f,2.5f,-1.51f), Vector3(0.0f, -1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.4f), 0.01f, 30.0f, 70.0f);
        AddSpotLight(Vector3(-0.35f,2.6f,0.21f), Vector3(0.0f, -1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.4f), 0.01f, 30.0f, 70.0f);

        AddSpotLight(Vector3(-3.00f,2.0f,-7.41f), Vector3(0.0f, -1.0f, 0.0f), Vector3(1.0f, 1.0f, 0.4f), 0.01f, 30.0f, 70.0f);

        AddSpotLight(Vector3(0.56f,1.7f,2.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 0.4f), 0.01f, 22.0f, 30.0f);





    }


    //AudioSource*  AddAudio(const std::string& name ,const std::string& filePath, const Vector3& position)
    //{
    //    Entity audioEntity = m_currentScene->CreateEntity("AudioSource");

    //    Transform* transform = &audioEntity.AddComponent<Transform>();

    //    transform->SetPosition(position);

    //    Audio::AudioSource* source = AudioManager::GetInstance().CreateSource(audioEntity);


    //    SharedPtr<AudioClip> clip = GetCurrent().GetAudioLibrary()->LoadAudio(name,filePath);
    //    

    //    if (clip != nullptr)
    //    {
    //        source->SetAudioClip(clip);
    //        source->SetLoop(true);
    //        
    //    }
 
    //    return source;

    //}


    //void AddOccluder(const Vector3& position, const Vector3 rotation, const Vector2& dimentions)
    //{

    //    Entity audioOccluder = m_currentScene->CreateEntity("AudioOccluder");

    //    Transform* transform = &audioOccluder.AddComponent<Transform>();

    //    transform->SetPosition(position);
    //    transform->SetEularRotation(rotation);


    //    Audio::AudioGeometry* geo = AudioManager::GetInstance().CreateGeometry(audioOccluder);

    //    AudioManager::GetInstance().AddOcclusionPolygon(geo, transform, dimentions);

    //   // wallEntity.AddComponent<>
    //}

    void AddDirLight(const Vector3& position, const Vector3& rotation,const Vector3& color, const float intensity)
    {
        Entity dirLight = m_currentScene->CreateEntity("DirectionalLight");

        Transform& transform = dirLight.AddComponent<Transform>();
        transform.SetPosition(position);
        transform.SetEularRotation(rotation);

        Light& light = dirLight.AddComponent<Light>();
        light.type = LightType::DirectionLight;
        light.color = color;
        light.intensity = intensity <= 0.0f ? 0.0f : intensity;
        light.direction = transform.GetForwardVector();

     

    }

    void AddPointLight(const Vector3& position,const Vector3& color, const float intensity, const float radius)
    {
        Entity pointLight = m_currentScene->CreateEntity("PointlLight");

        Transform& transform = pointLight.AddComponent<Transform>();
        transform.SetPosition(position);
        transform.SetEularRotation(Vector3(0.0f));

        Light& light = pointLight.AddComponent<Light>();
        light.type = LightType::PointLight;
        light.color = color;
        light.intensity = intensity <= 0.0f ? 0.0f : intensity;

        light.radius = radius <= 0.0f ? 0.0f : radius;
        

    }

    void  AddSpotLight(const Vector3& position, const Vector3& direction, const Vector3& color, const float intensity, const float innerAngle, const float outerAngle)
    {
        Entity pointLight = m_currentScene->CreateEntity("SpotlLight");

        Transform& transform = pointLight.AddComponent<Transform>();

        transform.SetPosition(position);
        transform.SetEularRotation(Vector3(0.0f));

        Light& light = pointLight.AddComponent<Light>();
        light.type = LightType::SpotLight;
        light.color = color;
        light.intensity = intensity <= 0.0f ? 0.0f : intensity;
        light.direction = direction;

        
        light.innerAngle = innerAngle > 0.1f ? innerAngle : 0.1f;
        light.innerAngle = cos(Radians(light.innerAngle));
        light.outerAngle = outerAngle > 0.2f ? outerAngle : 0.2f;
        light.outerAngle = cos(Radians(light.outerAngle));
      


    }


    void LerpLight()
    {

        float lerpFactor = EditorGUI::RuntimeEditor::LightLerp;

        
        ComponentView lighView = GetCurrentScene()->GetEntityManager()->GetComponentsOfType<Light>();

        
        SetSkyIntensity(Lerp(0.1f,1.0f,lerpFactor));

        int count = nightData.size() - 1;
        for (Entity light : lighView)
        {
            Light& lightcomp = light.GetComponent<Light>();

            lightcomp.intensity =  Lerp(nightData[count].intensity, dayData[count].intensity, lerpFactor);

            count--;
        }


        
    }

 

    void OnUpdate(float deltaTime)
    {
        // Input map for switching between the Wireframe and normal displays
        if (Input::InputSystem::GetInstance().GetKeyDown(Input::Key::G))
        {
            GetCurrent().GetAppWindow().ToggleWireframe();
        }

        LerpLight();

        //Audio::AudioManager::GetInstance().Update(deltaTime);

    }





private:

    

    struct lightData
    {
        lightData(const float inten, const Vector3& Color)
        {
            intensity = inten;
            color = Color;
        }

        float intensity = 0.0f;
        Vector3 color = Vector3(1.0f);
    };


    SharedPtr<SceneParser> parser = nullptr;
    SharedPtr<SceneLoader> loader = nullptr;

    Transform* playerTransform = nullptr;


   // std::vector<Light*> lights;

    std::vector<lightData> dayData;
    std::vector<lightData> nightData;

    static float prevlerp;

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

