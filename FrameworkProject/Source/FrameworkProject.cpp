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
        arena->Init(20, 20);

        unitManager = Factory<UnitManager>::Create();

        unitManager->Init();
        unitManager->SetArena(arena->GetImp());

        unitManager->LoadLevel(0);

        //GetPhysicsEngine()->CreateRigidBody();
    }

    void OnUpdate(float deltaTime)
    {

        unitManager->Update(deltaTime);
    }


private:

    SharedPtr<UnitManager> unitManager;

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