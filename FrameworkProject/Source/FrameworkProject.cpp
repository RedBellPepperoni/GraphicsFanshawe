#include "GameEngine.h"
#include"Robotron/Units/BaseUnit.h"
#include "Robotron/Units/UnitManager.h"
#include "Robotron/Arena/ArenaImpl.h"
#include "Robotron/Arena/Arena.h"


using namespace Robotron;

class FrameworkApplication : public Application
{
    void OnInit()
    {
       
        arena = Arena::GetArena();
        arena->Init(40, 20);

       

        UnitManager::GetInstance().Init();
        UnitManager::GetInstance().SetArena(arena->GetImp());

        UnitManager::GetInstance().LoadLevel(0);

        //GetPhysicsEngine()->CreateRigidBody();
    }

    void OnUpdate(float deltaTime)
    {

        UnitManager::GetInstance().Update(deltaTime);
    }


private:

    

    Arena* arena;

};


int main(int argc, char* argv)
{
    // Creating a new Appinstance
    FrameworkApplication* app = new FrameworkApplication();

    //FilePath path = File::GetCurrentPath();

    // Always Initialize the App
    app->Initialize();
    // Running the Application
    app->Run();


    delete app;
}