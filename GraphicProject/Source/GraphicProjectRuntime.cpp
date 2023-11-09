#pragma once
#include "GameEngine.h"
#include "SceneParser.h"
#include "SceneLoader.h"


class GraphicProject : public Application
{
    void OnInit()
    {
        parser = Factory<SceneParser>::Create();
        loader = Factory<SceneLoader>::Create();

        parser->ParseScene("Engine\\Scene\\SceneOne.json");

        std::map<std::string, std::string> modelmap = parser->GetModelList();
       
        std::vector<ObjectData> objectmap = parser->GetObjectList();

        for (auto const& data : modelmap)
        {
            loader->LoadModel(data.first, data.second);
        }


        for (ObjectData object : objectmap)
        {
            loader->SpawnObject(object.meshName, object.position, object.rotation, object.scale);
        }


       // loader->SpawnObject("Ground", Vector3(0.0f), Vector3(0.0f), Vector3(1.0f));
       // loader->SpawnObject("Car", Vector3(0.0f), Vector3(0.0f), Vector3(1.0f));


    }

    void OnUpdate(float deltaTime)
    {

    }


   

    



private:

    SharedPtr<SceneParser> parser = nullptr;
    SharedPtr<SceneLoader> loader = nullptr;


};


int main(int argc, char* argv)
{
    // Creating a new Appinstance
    GraphicProject* app = new GraphicProject();

    //FilePath path = File::GetCurrentPath();

    // Always Initialize the App
    app->Initialize();
    // Running the Application
    app->Run();


    delete app;
}