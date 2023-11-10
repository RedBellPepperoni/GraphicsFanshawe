#pragma once
#include "GameEngine.h"
#include "SceneParser.h"
#include "SceneLoader.h"


class PhysicsProject : public Application
{
    void OnInit()
    {
        parser = Factory<SceneParser>::Create();
        loader = Factory<SceneLoader>::Create();



        //loader->LoadModel("Marble", "Assets\\SphereBlender.ply");
        //loader->LoadModel("Base", "Assets\\Physicsbase.ply");

        // parse the scene with the name
        parser->ParseScene("Engine\\Scene\\SceneOne.json");

        // Retrives the parsed models
        std::map<std::string, std::string> modelmap = parser->GetModelList();

        // Retrives the parsed object data
        std::vector<ObjectData> objectmap = parser->GetObjectList();


        // Load all the models from the model data list
        for (auto const& data : modelmap)
        {
            loader->LoadModel(data.first, data.second);
        }

        // Create objects according to the scene data
        for (ObjectData object : objectmap)
        {
            loader->SpawnMarbles(object.position);
        }


        loader->SpawnPhysicsSpace();
   

    }


    



    void OnUpdate(float deltaTime)
    {
        // Input map for switching between the Wireframe and normal displays
        if (Input::InputSystem::GetInstance().GetKeyDown(Input::Key::G))
        {
            GetCurrent().GetAppWindow()->ToggleWireframe();
        }

    }


  



private:

    SharedPtr<SceneParser> parser = nullptr;
    SharedPtr<SceneLoader> loader = nullptr;


};


int main(int argc, char* argv)
{
    // Creating a new Appinstance
    PhysicsProject* app = new PhysicsProject();

    //FilePath path = File::GetCurrentPath();

    // Always Initialize the App
    app->Initialize();
    // Running the Application
    app->Run();


    delete app;
}