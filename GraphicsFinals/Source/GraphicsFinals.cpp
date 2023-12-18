#pragma once
#include "GameEngine.h"

// SceneLoading
#include "SceneLoading/SceneLoader.h"
#include "SceneLoading/SceneParser.h"


class NetworkFinalProject : public Application
{
 

    void OnInit()
    {
        AddDirLight(Vector3(0.0f, 0.0f, 0.0f), Vector3(-20.0f, 20.0f, 0.0f), Vector3(1.0f, 1.0f, 1.00f), 1.0f);



    
    }


    void OnUpdate(float deltaTime)
    {
        

      
        
    }



    void LoadSceneGeometry()
    {   
      

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

 
};



int main(int argc, char* argv)
{
    // Creating a new Appinstance
    NetworkFinalProject* app = new NetworkFinalProject();

    //FilePath path = File::GetCurrentPath();

    // Always Initialize the App
    app->Initialize();
    // Running the Application
    app->Run();


    delete app;
}