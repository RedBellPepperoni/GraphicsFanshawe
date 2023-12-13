#pragma once
#include "GameEngine.h"

// SceneLoading
#include "SceneLoading/SceneLoader.h"
#include "SceneLoading/SceneParser.h"


class GraphicsFinals : public Application
{
    struct LightData
    {
        float radius;
        float intensity;
    };


    void OnInit()
    {
        parser = Factory<SceneParser>::Create();
        loader = Factory<SceneLoader>::Create();

        LoadSceneGeometry();
       // AddTransparentObject(Vector3(0.0f, 0.0f, 5.0f));

        AddDirLight(Vector3(0.0f, 0.0f, 0.0f), Vector3(-20.0f, 20.0f, 0.0f), Vector3(1.0f, 1.0f, 1.00f), 1.0f);



        Vector3 color = Vector3(1.0f, 0.6f, 0.1f);
        float intensity = 10.0f;
        float radius = 20.0f;

       
       

       

        AddTorchLight(Vector3(-22.47f, 16.0f, -113.07f), radius, color, intensity);
        AddTorchLight(Vector3(25.00f, 11.0f, -95.54f), radius, color, intensity);
        AddTorchLight(Vector3(99.55f, 11.0f, -199.15f), radius, color, intensity);
        AddTorchLight(Vector3(99.59f, 11.0f, -156.81f), radius, color, intensity);
        AddTorchLight(Vector3(119.74f, 11.0f, -86.76f), radius, color, intensity);
        AddTorchLight(Vector3(54.51f, 11.0f, -147.58f), radius, color, intensity);

        
        SpawnBeholder(Vector3(76.0f, 14.0f, -199.0f), Vector3(0.0f, 180.0f, 0.0f), Vector3(3.0f, 3.0f, 3.0f));
  
        Vector3 direction = -Vector3(73.33f, 18.68f, -196.97f) + Vector3(73.39f,19.12f,-197.64);

        //SpawnSpotLight(Vector3(73.33f,18.68f , -196.97f), direction, Vector3());
    
    
    }


    void OnUpdate(float deltaTime)
    {
        

        if (Grow)
        {
            for (Light* light : pointlightArray)
            {
                light->radius += deltaTime * 20.0f;
                light->intensity += deltaTime * 10.0f;
            }


            for (Transform* firetransform : fireTransforms)
            {
                float Yscale = firetransform->GetScale().y + deltaTime * 2.0f;

                firetransform->SetScale(Vector3(2.0f, Yscale, 2.0f));
            }
        }

        else
        {
            for (Light* light : pointlightArray)
            {
                light->radius -= deltaTime * 20.0f;
                light->intensity -= deltaTime * 10.0f;
            }

            for (Transform* firetransform : fireTransforms)
            {
                float Yscale = firetransform->GetScale().y - deltaTime * 2.0f;

                firetransform->SetScale(Vector3(2.0f, Yscale, 2.0f));
            }

        }



        currenttime += deltaTime;


        if (currenttime > fadeTime)
        {
            currenttime = 0.0f;


            Grow = !Grow;
        }
        
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



    void AddTorchLight(const Vector3& position, const float radius, const Vector3& color, const float intensity)
    {

        Entity pointLight = m_currentScene->CreateEntity("TorchLight_");

        Transform& transform = pointLight.AddComponent<Transform>();
        transform.SetPosition(position);
        transform.SetRotation(Quaternion(Radians(Vector3(0.0f))));

        Light* light = &pointLight.AddComponent<Light>();
        light->type = LightType::PointLight;
        light->radius = radius;
        light->color = color;
        light->intensity = intensity <= 0.0f ? 0.0f : intensity;


       // light.direction = Normalize(transform.GetForwardVector());

        pointlightArray.push_back(light);

        Entity fireEntity = m_currentScene->CreateEntity("FireBillboard");

        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("Fire")->GetMeshes()[0];

        fireEntity.AddComponent<MeshComponent>(mesh);

        SharedPtr<Material> mat = fireEntity.AddComponent<MeshRenderer>().GetMaterial();

        mat->textureMaps.albedoMap = GetTextureLibrary()->GetResource("FireAlbedo");
        mat->metallic = 0.0f;
        mat->roughness = 0.0f;


        Transform* fireTrans = &fireEntity.AddComponent<Transform>(); 
        fireTrans->SetPosition(position - Vector3(0.0,5.0f,0.0f));
        fireTrans->SetRotation(Quaternion(Radians(Vector3(0.0f))));
        fireTrans->SetScale(Vector3(2.0f, 2.0f, 2.0f));
        fireTransforms.push_back(fireTrans);


    }





    void AddTransparentObject(const Vector3 pos)
    {
        std::string name = "Transparent_";

        Entity entity = GetCurrentScene()->CreateEntity(name);

        Transform* transform = &entity.AddComponent<Transform>();

        transform->SetPosition(pos);
        transform->SetRotation(Quaternion(Radians(Vector3(0.0f))));
        transform->SetScale(Vector3(0.02f));
        //transform->SetScale(Vector3(1.0f,1.0f,1.0f));


        //PhysicsProperties


        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("CrystalClusterOne")->GetMeshes()[0];
        //SharedPtr<Mesh> mesh = modelLibrary->GetResource("Ground")->GetMeshes()[0];

        entity.AddComponent<MeshComponent>(mesh);
        SharedPtr<Material> material = entity.AddComponent<MeshRenderer>().GetMaterial();

        material->textureMaps.albedoMap = GetTextureLibrary()->GetResource("DefaultAlbedo");
        material->albedoColour = Vector4(0.0f,0.2f,1.0f,0.7f);
        material->metallic = 0.6f;
        material->type = MaterialType::Transparent;





    }



    void SpawnBeholder(const Vector3& position, const Vector3& rotation, const Vector3& scale)
    {
        Entity beholder = m_currentScene->CreateEntity("Beholder");

        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("Beholder")->GetMeshes()[0];

        beholder.AddComponent<MeshComponent>(mesh);

        SharedPtr<Material> mat = beholder.AddComponent<MeshRenderer>().GetMaterial();

        mat->textureMaps.albedoMap = GetTextureLibrary()->GetResource("BeholderAlbedo");
        mat->metallic = 0.0f;
        mat->roughness = 0.0f;


        Transform* beholderTrans = &beholder.AddComponent<Transform>();
        beholderTrans->SetPosition(position);
        beholderTrans->SetRotation(Quaternion(Radians(rotation)));
        beholderTrans->SetScale(scale);
        

    }


    void SpawnSpotLight(const Vector3& position, const Vector3& direction, const Vector3& color)
    {
        Entity dirLight = m_currentScene->CreateEntity("DirectionalLight");

        Transform& transform = dirLight.AddComponent<Transform>();
        transform.SetPosition(position);
        //transform.SetRotation(Quaternion(Radians(rotation)));

        Light& light = dirLight.AddComponent<Light>();
        light.type = LightType::SpotLight;
        light.color = color;
        light.intensity = 10.0f;
        light.innerAngle = 5.0f;
        light.outerAngle = 5.5f;

        light.direction = Normalize(direction);
    }


private:

    SharedPtr<SceneParser> parser = nullptr;
    SharedPtr<SceneLoader> loader = nullptr;



    std::vector<Transform*> fireTransforms;
    std::vector<Light*> pointlightArray;
    LightData lightmin;
    LightData lightmax;




    bool Grow = false;
    float fadeTime = 0.05f;
    float currenttime = 0.0f;
    float lerpfactor = 0.0f;

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