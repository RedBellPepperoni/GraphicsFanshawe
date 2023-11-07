#include "GameEngine.h"
#include"Robotron/Units/BaseUnit.h"
#include "Robotron/Units/UnitManager.h"


using namespace Robotron;

class FrameworkApplication : public Application
{
    void OnInit()
    {
       
        unitManager = Factory<UnitManager>::Create();

        unitManager->Init();

        unitManager->LoadLevel(0);

        //GetPhysicsEngine()->CreateRigidBody();
    }

    void OnUpdate(float deltaTime)
    {

        unitManager->Update(deltaTime);
    }


private:

    SharedPtr<UnitManager> unitManager;

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