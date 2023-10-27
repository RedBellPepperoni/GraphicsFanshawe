#include "GameEngine.h"




class GraphicApp : public Application
{

private:

    int m_entitycounter = 0;

    void CreateMeshObject(const std::string& resourcename, const Vector3& position, const Vector3& rotation)
    {
        SharedPtr<Model> model = GetModelLibrary()->GetResource(resourcename);
        CHECKNULL(model);

        std::string entityName = "Entity_" + std::to_string(m_entitycounter);

        Entity Object = GetCurrentScene()->CreateEntity(entityName);


        // Add a Trasnform. later make sure every spawnd entity has an auto attached transform
        Object.AddComponent<Transform>();
        Object.GetComponent<Transform>().SetPosition(position); 
        Object.GetComponent<Transform>().SetRotation(Vector3(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z)));
        Object.AddComponent<MeshComponent>(model->GetMeshes()[0]);
        Object.AddComponent<MeshRenderer>();

        m_entitycounter += 1;

    }



    void LoadSceneModels()
    {

        // Loading a new Resource from the Disk and storing the reference in the Model lirary for future use
        SharedPtr<Model> wallModel = GetModelLibrary()->LoadModel("Wall", "Assets\\Geometry\\SM_Env_Wall_10_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(wallModel);

        wallModel = GetModelLibrary()->LoadModel("ConWall", "Assets\\Geometry\\SM_Env_Construction_Wall_01_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(wallModel);

        wallModel = GetModelLibrary()->LoadModel("BathTub", "Assets\\bathtub.ply");
        CHECKNULL(wallModel);

        wallModel = GetModelLibrary()->LoadModel("Floor", "Assets\\Geometry\\SM_Env_Floor_02_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(wallModel);

        wallModel = GetModelLibrary()->LoadModel("PlantWall", "Assets\\Geometry\\SM_Env_PlantWall_02_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(wallModel);
    }


    void BuildScene()
    {
// Floooor

        int floorlinecount = 8;
        float startpoint = -10.0f;

        for (int i = 0; i <= floorlinecount; i++)
        {
            float zLoc = startpoint + (i* 5.0f);

            CreateMeshObject("Floor", Vector3(30.0f, 0.0f, zLoc), Vector3(0.0f));
            CreateMeshObject("Floor", Vector3(25.0f, 0.0f, zLoc), Vector3(0.0f));
            CreateMeshObject("Floor", Vector3(20.0f, 0.0f, zLoc), Vector3(0.0f));
            CreateMeshObject("Floor", Vector3(15.0f, 0.0f, zLoc), Vector3(0.0f));
            CreateMeshObject("Floor", Vector3(10.0f, 0.0f, zLoc), Vector3(0.0f));
            CreateMeshObject("Floor", Vector3(5.0f, 0.0f, zLoc), Vector3(0.0f));
            CreateMeshObject("Floor", Vector3(0.0f, 0.0f, zLoc), Vector3(0.0f));
            CreateMeshObject("Floor", Vector3(-5.0f, 0.0f, zLoc), Vector3(0.0f));
            CreateMeshObject("Floor", Vector3(-10.0f, 0.0f, zLoc), Vector3(0.0f));
            CreateMeshObject("Floor", Vector3(-15.0f, 0.0f, zLoc), Vector3(0.0f));

        }
      


        // First Wall

        int wallHeight = 3;

        for (int i = 0; i <= wallHeight; i++)
        {
            float yPos = i * 5.0f;
            CreateMeshObject("ConWall", Vector3(-20.0f, yPos, -10.0f), Vector3(0.0f));
            CreateMeshObject("ConWall", Vector3(-10.0f, yPos, -10.0f), Vector3(0.0f));
            CreateMeshObject("ConWall", Vector3(0.0f, yPos, -10.0f), Vector3(0.0f));
            CreateMeshObject("ConWall", Vector3(10.0f, yPos, -10.0f), Vector3(0.0f));
            CreateMeshObject("ConWall", Vector3(20.0f, yPos, -10.0f), Vector3(0.0f));
        }

        //Second Wall 

        for (int i = 0; i <= wallHeight; i++)
        {
            float yPos = i * 5.0f;

            CreateMeshObject("ConWall", Vector3(30.0f, yPos, -10.0f), Vector3(0.0f, -90.0f, 0.0f));
            CreateMeshObject("ConWall", Vector3(30.0f, yPos, 0.0f), Vector3(0.0f, -90.0f, 0.0f));
            CreateMeshObject("ConWall", Vector3(30.0f, yPos, 10.0f), Vector3(0.0f, -90.0f, 0.0f));
            CreateMeshObject("ConWall", Vector3(30.0f, yPos, 20.0f), Vector3(0.0f, -90.0f, 0.0f));
        }

       

       // Forth Wall
        for (int i = 0; i <= wallHeight; i++)
        {
            float yPos = i * 5.0f;

            CreateMeshObject("ConWall", Vector3(-20.0f, yPos, 0.0f), Vector3(0.0f, 90.0f, 0.0f));
            CreateMeshObject("ConWall", Vector3(-20.0f, yPos, 10.0f), Vector3(0.0f, 90.0f, 0.0f));
            CreateMeshObject("ConWall", Vector3(-20.0f, yPos, 20.0f), Vector3(0.0f, 90.0f, 0.0f));
            CreateMeshObject("ConWall", Vector3(-20.0f, yPos, 30.0f), Vector3(0.0f, 90.0f, 0.0f));

        }

      

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






