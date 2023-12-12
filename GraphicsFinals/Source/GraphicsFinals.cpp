#pragma once
#include "GameEngine.h"

// SceneLoading
#include "SceneLoading/SceneLoader.h"
#include "SceneLoading/SceneParser.h"


class GraphicsFinals : public Application
{
    void OnInit()
    {
        parser = Factory<SceneParser>::Create();
        loader = Factory<SceneLoader>::Create();

        LoadSceneGeometry();

        AddDirLight(Vector3(0.0f, 0.0f, 0.0f), Vector3(-20.0f, 10.0f, 0.0f), Vector3(1.0f, 1.0f, 0.85f), 1.0f);

    }


    void OnUpdate(float deltaTime)
    {




    }



    void LoadSceneGeometry()
    {   
        // parse the scene with the name
        parser->ParseScene("Engine\\Scene\\SceneDungeon.json");

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


private:

    SharedPtr<SceneParser> parser = nullptr;
    SharedPtr<SceneLoader> loader = nullptr;

};



int main(int argc, char* argv)
{
    // Creating a new Appinstance
    GraphicsFinals* app = new GraphicsFinals();

    //FilePath path = File::GetCurrentPath();

    // Always Initialize the App
    app->Initialize();
    // Running the Application
    app->Run();


    delete app;
}