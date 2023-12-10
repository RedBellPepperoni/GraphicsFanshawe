#include "GameEngine.h"

class FrameworkProject : public Application
{
    void OnInit()
    {

    }


    void OnUpdate(float deltaTime)
    {

    }


};




int main(int argc, char* argv)
{
    // Creating a new Appinstance
    FrameworkProject* app = new FrameworkProject();

    //FilePath path = File::GetCurrentPath();

    // Always Initialize the App
    app->Initialize();
    // Running the Application
    app->Run();


    delete app;
}