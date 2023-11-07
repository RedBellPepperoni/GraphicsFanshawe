#include "GameEngine.h"

class GraphicApplication : public Application
{
    void OnInit()
    {
        Entity newEntity = GetCurrentScene()->CreateEntity("Entity_01");

        newEntity.AddComponent<Transform>();


    }



};


int main(int argc, char* argv)
{
    // Creating a new Appinstance
    GraphicApplication* app = new GraphicApplication();

    //FilePath path = File::GetCurrentPath();

    // Always Initialize the App
    app->Initialize();
    // Running the Application
    app->Run();


    delete app;
}