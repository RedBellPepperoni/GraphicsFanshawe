#pragma once
#include "GameEngine.h"
#include "Engine/Core/Network/NetworkComponent.h"
#include "Engine/Core/Network/NetworkManager.h"


using namespace FanshaweGameEngine::Network;

class NetworkFinalProject : public Application
{




    void OnInit()
    {
        AddDirLight(Vector3(0.0f, 0.0f, 0.0f), Vector3(-45.0f, 3.6f, 0.0f), Vector3(1.0f, 1.0f, 1.00f), 1.0f);


        GetModelLibrary()->LoadModel("Character", "Assets\\Models\\AmongUs.fbx");

        GetTextureLibrary()->LoadTexture("CharacterAlbedo", "Assets\\Textures\\amonguspink.png",TextureFormat::RGB);

      

        networkManager.Initialize();

        CreateNetworkPlayer();


        CreateNetworkOtherPlayers(0);
        CreateNetworkOtherPlayers(1);
        CreateNetworkOtherPlayers(2);
        CreateNetworkOtherPlayers(3);

    }


    void OnUpdate(float deltaTime)
    {

        Vector3 playerPosition = playerTransform->GetPosition();
        Vector3 playerRotation = playerTransform->GetEulerRotation();

       
     

        if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::Up))
        {
            playerPosition = playerTransform->GetPosition();
            playerTransform->SetPosition(Vector3(playerPosition.x, 0.0f, playerPosition.z - 10 * deltaTime));
            lastdirection.z = -1.0f;
           
        }

        else if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::Down))
        {
            playerPosition = playerTransform->GetPosition();
            playerTransform->SetPosition(Vector3(playerPosition.x, 0.0f, playerPosition.z + 10 * deltaTime));
            lastdirection.z = 1.0f;
            
        }

        if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::Left))
        {
            playerPosition = playerTransform->GetPosition();
            playerTransform->SetPosition(Vector3(playerPosition.x - 10 * deltaTime, 0.0f, playerPosition.z ));
            lastdirection.x = -1.0f;
            
        }

        else if (Input::InputSystem::GetInstance().GetKeyHeld(Input::Key::Right))
        {
           playerPosition = playerTransform->GetPosition();
           playerTransform->SetPosition(Vector3(playerPosition.x + 10 * deltaTime, 0.0f, playerPosition.z));
           lastdirection.x = 1.0f;
        }

        lastdirection.y = 0.0f;
        
        lastdirection = Normalize(lastdirection);

       // Vector3 lookAtDirection = playerPosition + lastdirection * 10.0f;

        Quaternion rotation = LookAtRotation(lastdirection, Vector3(0.0f, 1.0f, 0.0f));

        playerTransform->SetRotation(rotation);
      
        playerPosition = playerTransform->GetPosition();

        networkManager.SendPlayerPositionToServer(playerPosition.x,playerPosition.z);

        networkManager.Update(deltaTime);






        ComponentView view = GetCurrentScene()->GetEntityManager()->GetComponentsOfType<NetworkComponent>();

        int count = 0;
        for (Entity entity : view)
        {
            Transform& transform = entity.GetComponent<Transform>();

            float positionX = networkManager.m_NetworkedPositions[0].x;
            float positionZ = networkManager.m_NetworkedPositions[0].z;

            transform.SetPosition(Vector3(positionX, 0.0f, positionZ));
        }


    }



    void CreateNetworkPlayer()
    {
        Entity networkEntity = GetCurrentScene()->CreateEntity("NetworkEntity");

        playerTransform = &networkEntity.AddComponent<Transform>();
        playerTransform->SetPosition(Vector3(0.0f));
        playerTransform->SetRotation(Quaternion(Radians(Vector3(0.0f))));


        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("Character")->GetMeshes()[0];
        
        networkEntity.AddComponent<MeshComponent>(mesh);


        SharedPtr<Material> material = networkEntity.AddComponent<MeshRenderer>().GetMaterial();

        material->albedoColour = Vector4(0.0,0.0f,0.0f,1.0f);
        material->textureMaps.albedoMap = GetTextureLibrary()->GetResource("CharacterAlbedo");
        material->metallic = 0.5f;
        material->roughness = 0.0f;

        material->type = MaterialType::Opaque;

    }


    void CreateNetworkOtherPlayers(int playerNumber)
    {

        std::string name = "NetworkEntity_" + std::to_string(playerNumber);

        Entity networkEntity = GetCurrentScene()->CreateEntity(name);

        Transform& transform = networkEntity.AddComponent<Transform>();
        transform.SetPosition(Vector3(0.0f));
        transform.SetRotation(Quaternion(Radians(Vector3(0.0f))));


        networkEntity.AddComponent<NetworkComponent>();


        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("Character")->GetMeshes()[0];

        networkEntity.AddComponent<MeshComponent>(mesh);


        SharedPtr<Material> material = networkEntity.AddComponent<MeshRenderer>().GetMaterial();


        material->albedoColour = Vector4(0.8f, 0.6f, 0.61f, 1.0f);
       // material->textureMaps.albedoMap = GetTextureLibrary()->GetResource("CharacterAlbedo");
        material->metallic = 0.7f;
        material->roughness = 0.02f;

        material->type = MaterialType::Opaque;

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



    NetworkManager networkManager;

    Transform* playerTransform = nullptr;

    Vector3 lastdirection = Vector3(0.0f, 0.0f, -1.0f);

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