#pragma once
// The actual engine
#include "GameEngine.h"
#include "Framework/Game/Game.h"



class FrameworkApp : public Application
{
   


private:

    Framework::Game m_game;


public:




    void OnInit()
    {
        LOG_CRITICAL("This is a CRITICAL Log message");
        LOG_ERROR("This is a ERROR Log message");
        LOG_WARN("This is a WARN Log message");
        LOG_INFO("This is a INFO Log message");
        LOG_TRACE("This is a TRACE Log message");


       



          // Loading a new Resource from the Disk and storing the reference in the Model lirary for future use
       SharedPtr<Model> model = GetModelLibrary()->LoadModel("Board", "Assets\\Berzerk_Level_Ouput.ply");
       CHECKNULL(model);

       SharedPtr<Model> robotmodel = GetModelLibrary()->LoadModel("Robot", "Assets\\robot.ply");
       CHECKNULL(robotmodel);


;

         // Using ECS now
        Entity boardObject = GetCurrentScene()->CreateEntity("BathObject");

        // Add a Trasnform. later make sure every spawnd entity has an auto attached transform
        boardObject.AddComponent<Transform>();
        boardObject.GetComponent<Transform>().SetPosition(Vector3(0.0f ,0.0f, 60.0f));



        // Making the board flat with the ground
        boardObject.GetComponent<Transform>().SetRotation(Quaternion(Vector3(glm::radians(-90.0f), 0.0f, 0.0f)));

        // Set the First mesh reference as out mesh component
        // Later need to make this automatically generate entities for multiple meshes
        boardObject.AddComponent<MeshComponent>(model->GetMeshes()[0]);
        boardObject.AddComponent<MeshRenderer>();

        boardObject.GetComponent<MeshRenderer>().GetMaterial()->albedoColour = Vector4(0.0f,0.0f,0.0f,1.0f);



        
      m_game.GenerateGameBoard("Assets\\Berzerk_Level_1193265.txt");

        // hard coding friendIds for now
        m_game.CreateRobot(1,Vector2Int(2, 1), robotmodel);
        m_game.CreateRobot(0,Vector2Int(2, 3), robotmodel);

        m_game.CreateRobot(3,Vector2Int(80, 7), robotmodel);
        m_game.CreateRobot(2,Vector2Int(75, 1), robotmodel);

        m_game.CreateRobot(5,Vector2Int(50, 10), robotmodel);
        m_game.CreateRobot(4,Vector2Int(49, 8), robotmodel);

        m_game.CreateRobot(7,Vector2Int(30, 80), robotmodel);
        m_game.CreateRobot(6,Vector2Int(29, 78), robotmodel);

        m_game.CreateRobot(9,Vector2Int(12, 20), robotmodel);
        m_game.CreateRobot(8,Vector2Int(14, 19), robotmodel);
       


       

        
       
    }

    void OnUpdate(float deltaTime)
    {

        m_game.Update(deltaTime);

    }

};



int main(int argc, char* argv)
{
    UniquePtr<FrameworkApp> app = MakeUnique<FrameworkApp>();

    app->Initialize();

    app->Run();

}