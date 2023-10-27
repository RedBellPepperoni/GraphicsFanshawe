#include "GameEngine.h"




class GraphicApp : public Application
{

private:

    void LoadSceneModels()
    {

        // Loading a new Resource from the Disk and storing the reference in the Model lirary for future use
        SharedPtr<Model> wallModel = GetModelLibrary()->LoadModel("Wall", "Assets\\Geometry\\SM_Env_Wall_01_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(wallModel);


        wallModel = GetModelLibrary()->LoadModel("Floor", "Assets\\Geometry\\SM_Env_Floor_02_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(wallModel);

        wallModel = GetModelLibrary()->LoadModel("PlantWall", "Assets\\Geometry\\SM_Env_PlantWall_02_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(wallModel);
    }


    void BuildScene()
    {
        SharedPtr<Model> wallModel01 = GetModelLibrary()->GetResource("Floor");
        CHECKNULL(wallModel01);

        Entity wallObject = GetCurrentScene()->CreateEntity("Wall_01_01");

        // Add a Trasnform. later make sure every spawnd entity has an auto attached transform
        wallObject.AddComponent<Transform>();
        wallObject.GetComponent<Transform>().SetPosition(Vector3(0.0f));
        wallObject.GetComponent<Transform>().SetRotation(Vector3(0.0f, 0.0f, 0.0f));

        // Set the First mesh reference as out mesh component
        // Later need to make this automatically generate entities for multiple meshes
        wallObject.AddComponent<MeshComponent>(wallModel01->GetMeshes()[0]);
        wallObject.AddComponent<MeshRenderer>();


    }

public:



    void OnInit()
    {

        LOG_CRITICAL("This is a CRITICAL Log message");
        LOG_ERROR("This is a ERROR Log message");
        LOG_WARN("This is a WARN Log message");
        LOG_INFO("This is a INFO Log message");
        LOG_TRACE("This is a TRACE Log message");


        LoadSceneModels();

        BuildScene();


        //  // Loading a new Resource from the Disk and storing the reference in the Model lirary for future use
        //SharedPtr<Model> model = GetModelLibrary()->LoadModel("Bathtub", "Assets\\bathtub.ply");
        //CHECKNULL(model);




        //// SharedPtr<GameObject> bathObject;
        // //SharedPtr<GameObject> sphereObject;

        // // Using ECS now
        //Entity bathObject = GetCurrentScene()->CreateEntity("BathObject");
        //Entity sphereObject = GetCurrentScene()->CreateEntity("sphere_01");



        //// Add a Trasnform. later make sure every spawnd entity has an auto attached transform
        //bathObject.AddComponent<Transform>();
        //bathObject.GetComponent<Transform>().SetPosition(Vector3(0.0f));
        //bathObject.GetComponent<Transform>().SetRotation(Vector3(0.0f, 0.0f, 0.0f));

        //// Set the First mesh reference as out mesh component
        //// Later need to make this automatically generate entities for multiple meshes
        //bathObject.AddComponent<MeshComponent>(model->GetMeshes()[0]);


        //bathObject.AddComponent<MeshRenderer>();





    }


    void OnUpdate(float deltaTime)
    {


        // LOG_INFO("Deltatime : {0}", GetDelta());


    }



};


int main(int argc, char* argv)
{
    // Creating a new Appinstance
    GraphicApp* app = new GraphicApp();

    //FilePath path = File::GetCurrentPath();

    // Always Initialize the App
    app->Initialize();
    // Running the Application
    app->Run();
}






