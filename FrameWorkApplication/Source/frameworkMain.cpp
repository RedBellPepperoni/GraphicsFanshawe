#include "GameEngine.h"


using namespace FanshaweGameEngine;

class FrameworkProject : public Application
{
    void OnInit()
    {



        Entity mainController = GetCurrentScene()->CreateEntity("Controller");
        Transform& controllerTransform = mainController.AddComponent<Transform>();

        LuaScriptComponent& mainluaComp = mainController.AddComponent<LuaScriptComponent>();
        mainluaComp.LoadScript("Assets\\Scripts\\commandmain.lua");

 

        GetModelLibrary()->LoadModel("Drone", "Assets\\Models\\Drone.fbx");

        Entity entity = GetCurrentScene()->CreateEntity("Drone");

        Transform& transform = entity.AddComponent<Transform>();
        transform.SetScale(Vector3(5.0f));

        SharedPtr<Mesh> mesh = GetModelLibrary()->GetResource("Drone")->GetMeshes()[0];

        entity.AddComponent<MeshComponent>(mesh);
        entity.AddComponent<MeshRenderer>();

     

        LuaScriptComponent& luaComp = entity.AddComponent<LuaScriptComponent>();

        luaComp.LoadScript("Assets\\Scripts\\Test.lua");





     

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