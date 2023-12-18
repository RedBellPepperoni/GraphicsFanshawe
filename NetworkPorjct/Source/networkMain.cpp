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

        networkManager = MakeShared<NetworkManager>();

        networkManager->Initialize();

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


        if (LengthSquared(lastdirection) < 0.5f)
        {
            lastdirection = Vector3(0.0f, 0.0f, -1.0f);
        }

        playerPosition = playerTransform->GetPosition();

        Vector3 position = Vector3(playerPosition.x, 0.0f, playerPosition.z);

        networkManager->SendPlayerData(position, lastdirection);

        networkManager->Update(deltaTime);
   
        lastdirection = Normalize(lastdirection);

       // Vector3 lookAtDirection = playerPosition + lastdirection * 10.0f;

        Quaternion rotation = LookAtRotation(lastdirection, Vector3(0.0f, 1.0f, 0.0f));

        playerTransform->SetRotation(rotation);
      
       

        for (int index = 0; index < networkEntityTransforms.size(); index++)
        {
               

                float positionX = networkManager->m_NetworkedPositions[index].positionX / 100.0f;
                float positionZ = networkManager->m_NetworkedPositions[index].positionZ/ 100.0f;

                float directionX = networkManager->m_NetworkedPositions[index].directionX / 100.0f;
                float directionZ = networkManager->m_NetworkedPositions[index].directionZ / 100.0f;
                networkEntityTransforms[index]->SetPosition(Vector3(positionX, 0.0f, positionZ));



                Vector3 newDirection = (Vector3(directionX, 0.0f, directionZ));

                if (LengthSquared(newDirection) < 0.5f)
                {
                    newDirection = Vector3(0.0f, 0.0f, -1.0f);
                }


                Quaternion rotation = LookAtRotation(Normalize(newDirection), Vector3(0.0f, 1.0f, 0.0f));
                networkEntityTransforms[index]->SetRotation(rotation);

              
        }




        //ComponentView view = GetCurrentScene()->GetEntityManager()->GetComponentsOfType<NetworkComponent>();

        //int count = 0;
        //for (Entity entity : view)
        //{
        //    Transform& transform = entity.GetComponent<Transform>();

        //    float positionX = networkManager.m_NetworkedPositions[count].positionX / 100.0f;
        //    float positionZ = networkManager.m_NetworkedPositions[count].positionZ/ 100.0f;

        //    float directionX = networkManager.m_NetworkedPositions[count].directionX / 100.0f;
        //    float directionZ = networkManager.m_NetworkedPositions[count].directionZ / 100.0f;
        //    transform.SetPosition(Vector3(positionX, 0.0f, positionZ));



        //    Vector3 newDirection = (Vector3(directionX, 0.0f, directionZ));

        //    if (LengthSquared(newDirection) < 0.5f)
        //    {
        //        newDirection = Vector3(0.0f, 0.0f, -1.0f);
        //    }


        //    Quaternion rotation = LookAtRotation(Normalize(newDirection), Vector3(0.0f, 1.0f, 0.0f));
        //    transform.SetRotation(rotation);

        //  
        //   // LOG_INFO("Position : {0} , {1} ________________", positionX, positionZ);

        //    count++;

        //    
        //}
       


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

        Transform* transform = &networkEntity.AddComponent<Transform>();
        transform->SetPosition(Vector3(0.0f));
        transform->SetRotation(Quaternion(Radians(Vector3(0.0f))));


        networkEntity.AddComponent<NetworkComponent>();


        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("Character")->GetMeshes()[0];

        networkEntity.AddComponent<MeshComponent>(mesh);


        SharedPtr<Material> material = networkEntity.AddComponent<MeshRenderer>().GetMaterial();


        material->albedoColour = Vector4(0.8f, 0.6f, 0.61f, 1.0f);
       // material->textureMaps.albedoMap = GetTextureLibrary()->GetResource("CharacterAlbedo");
        material->metallic = 0.7f;
        material->roughness = 0.02f;

        material->type = MaterialType::Opaque;


        networkEntityTransforms.push_back(transform);

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



    SharedPtr<NetworkManager> networkManager;

    Transform* playerTransform = nullptr;

    Vector3 lastdirection = Vector3(0.0f, 0.0f, -1.0f);

private:

    std::vector<Transform*> networkEntityTransforms;
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