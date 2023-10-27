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
        SharedPtr<Model> model = GetModelLibrary()->LoadModel("Wall", "Assets\\Geometry\\SM_Env_Wall_10_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(model);

        model = GetModelLibrary()->LoadModel("ConWall", "Assets\\Geometry\\SM_Env_Construction_Wall_01_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(model);

        model = GetModelLibrary()->LoadModel("BathTub", "Assets\\bathtub.ply");
        CHECKNULL(model);

        model = GetModelLibrary()->LoadModel("Floor", "Assets\\Geometry\\SM_Env_Floor_02_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(model);

        model = GetModelLibrary()->LoadModel("PlantWall", "Assets\\Geometry\\SM_Env_PlantWall_02_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(model);

        model = GetModelLibrary()->LoadModel("ConBlock", "Assets\\Geometry\\SM_Env_Construction_Block_06_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(model);

        model = GetModelLibrary()->LoadModel("ConStair", "Assets\\Geometry\\SM_Env_Construction_Stairs_01_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(model);

        model = GetModelLibrary()->LoadModel("ConRail", "Assets\\Geometry\\SM_Env_Construction_Rail_01_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(model);

        model = GetModelLibrary()->LoadModel("Satellite", "Assets\\Geometry\\SM_Prop_Satellite_01_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(model);

        model = GetModelLibrary()->LoadModel("Rocket", "Assets\\Geometry\\SM_Prop_Rocket_01_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(model);

        model = GetModelLibrary()->LoadModel("DoorFrame", "Assets\\Geometry\\SM_Env_ControlRoom_Doorway_01_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(model);
        
        model = GetModelLibrary()->LoadModel("Door", "Assets\\Geometry\\SM_Env_ControlRoom_Door_01_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(model); 

        model = GetModelLibrary()->LoadModel("DeskOne", "Assets\\Geometry\\SM_Prop_Desk_01_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(model);


        model = GetModelLibrary()->LoadModel("DeskTwo", "Assets\\Geometry\\SM_Prop_Desk_02_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(model); 
        
        model = GetModelLibrary()->LoadModel("Shuttle", "Assets\\Geometry\\SM_Prop_Shuttle_01_xyz_n_rgba_uv_flatshaded_xyz_n_rgba.ply");
        CHECKNULL(model);
        

       


        
    }

    void BuildFloorCeling()
    {
        int floorlinecount = 12;
        float startpoint = -20.0f;

        for (int i = 0; i < floorlinecount; i++)
        {
            float zLoc = startpoint + (i * 5.0f);

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



            /*  CreateMeshObject("Floor", Vector3(30.0f, 20.0f, zLoc), Vector3(0.0f, 180.0f, 0.0f));
              CreateMeshObject("Floor", Vector3(25.0f, 20.0f, zLoc), Vector3(0.0f, 180.0f, 0.0f));
              CreateMeshObject("Floor", Vector3(20.0f, 20.0f, zLoc), Vector3(0.0f, 180.0f, 0.0f));
              CreateMeshObject("Floor", Vector3(15.0f, 20.0f, zLoc), Vector3(0.0f, 180.0f, 0.0f));
              CreateMeshObject("Floor", Vector3(10.0f, 20.0f, zLoc), Vector3(0.0f, 180.0f, 0.0f));
              CreateMeshObject("Floor", Vector3(5.0f, 20.0f, zLoc), Vector3(0.0f, 180.0f, 0.0f));
              CreateMeshObject("Floor", Vector3(0.0f, 20.0f, zLoc), Vector3(0.0f, 180.0f, 0.0f));
              CreateMeshObject("Floor", Vector3(-5.0f, 20.0f, zLoc), Vector3(0.0f, 180.0f, 0.0f));
              CreateMeshObject("Floor", Vector3(-10.0f, 20.0f, zLoc), Vector3(0.0f, 180.0f, 0.0f));
              CreateMeshObject("Floor", Vector3(-15.0f, 20.0f, zLoc), Vector3(0.0f, 180.0f, 0.0f));*/

        }
    }

    void BuildWalls()
    {

        // First Wall

        int wallHeight = 5;

        for (int i = 0; i < wallHeight; i++)
        {
            float yPos = i * 5.0f;
            CreateMeshObject("ConWall", Vector3(-20.0f, yPos, -20.0f), Vector3(0.0f));
            CreateMeshObject("ConWall", Vector3(-10.0f, yPos, -20.0f), Vector3(0.0f));
            CreateMeshObject("ConWall", Vector3(0.0f, yPos, -20.0f), Vector3(0.0f));
            CreateMeshObject("ConWall", Vector3(10.0f, yPos, -20.0f), Vector3(0.0f));
            CreateMeshObject("ConWall", Vector3(20.0f, yPos, -20.0f), Vector3(0.0f));
        }

        //Second Wall 

        for (int i = 0; i < wallHeight; i++)
        {
            float yPos = i * 5.0f;

            CreateMeshObject("ConWall", Vector3(30.0f, yPos, -20.0f), Vector3(0.0f, -90.0f, 0.0f));
            CreateMeshObject("ConWall", Vector3(30.0f, yPos, -10.0f), Vector3(0.0f, -90.0f, 0.0f));
            CreateMeshObject("ConWall", Vector3(30.0f, yPos, 0.0f), Vector3(0.0f, -90.0f, 0.0f));
            CreateMeshObject("ConWall", Vector3(30.0f, yPos, 10.0f), Vector3(0.0f, -90.0f, 0.0f));
            CreateMeshObject("ConWall", Vector3(30.0f, yPos, 20.0f), Vector3(0.0f, -90.0f, 0.0f));
            CreateMeshObject("ConWall", Vector3(30.0f, yPos, 30.0f), Vector3(0.0f, -90.0f, 0.0f));
           
        }



        // Forth Wall
        for (int i = 0; i < wallHeight; i++)
        {
            float yPos = i * 5.0f;

            CreateMeshObject("ConWall", Vector3(-20.0f, yPos, -10.0f), Vector3(0.0f, 90.0f, 0.0f));
            CreateMeshObject("ConWall", Vector3(-20.0f, yPos, 0.0f), Vector3(0.0f, 90.0f, 0.0f));
            CreateMeshObject("ConWall", Vector3(-20.0f, yPos, 10.0f), Vector3(0.0f, 90.0f, 0.0f));
            CreateMeshObject("ConWall", Vector3(-20.0f, yPos, 20.0f), Vector3(0.0f, 90.0f, 0.0f));
            CreateMeshObject("ConWall", Vector3(-20.0f, yPos, 30.0f), Vector3(0.0f, 90.0f, 0.0f));
            CreateMeshObject("ConWall", Vector3(-20.0f, yPos, 40.0f), Vector3(0.0f, 90.0f, 0.0f));
           

        }


        CreateMeshObject("ConWall", Vector3(-20.0f, 0.0f, 40.0f), Vector3(0.0f, 180.0f, 0.0f));
        CreateMeshObject("ConWall", Vector3(-10.0f, 0.0f, 40.0f), Vector3(0.0f, 180.0f, 0.0f));

        CreateMeshObject("ConWall", Vector3(0.0f, 0.0f, 40.0f), Vector3(0.0f, 180.0f, 0.0f));
        CreateMeshObject("ConWall", Vector3(20.0f, 0.0f, 40.0f), Vector3(0.0f, 180.0f, 0.0f));
        CreateMeshObject("ConWall", Vector3(30.0f, 0.0f, 40.0f), Vector3(0.0f, 180.0f, 0.0f));


    }

    void BuildWAlkwayStairs()
    {
        int numblock = 10;
        float startPos = -15.0f;
        
        for (int i = 0; i < numblock; i++)
        {
            float xPos = startPos + (i * 5.0f);

            CreateMeshObject("ConBlock", Vector3(xPos, 10.0f, 10.0f), Vector3(0.0f));
            CreateMeshObject("ConRail", Vector3(xPos, 15.0f, 5.0f), Vector3(0.0f,90.0f,0.0f));
            
            CreateMeshObject("Floor", Vector3(xPos, 15.02f, 5.0f), Vector3(0.0f));
        }


        CreateMeshObject("ConRail", Vector3(-15.0f, 15.0f, 10.0f), Vector3(0.0f, 90.0f, 0.0f));
        CreateMeshObject("ConRail", Vector3(-10.0f, 15.0f, 10.0f), Vector3(0.0f, 90.0f, 0.0f));
        CreateMeshObject("ConRail", Vector3(-5.0f, 15.0f, 10.0f), Vector3(0.0f, 90.0f, 0.0f));
        CreateMeshObject("ConRail", Vector3(-0.0f, 15.0f, 10.0f), Vector3(0.0f, 90.0f, 0.0f));
        CreateMeshObject("ConRail", Vector3(5.0f, 15.0f, 10.0f), Vector3(0.0f, 90.0f, 0.0f));
        CreateMeshObject("ConRail", Vector3(10.0f, 15.0f, 10.0f), Vector3(0.0f, 90.0f, 0.0f));
        CreateMeshObject("ConRail", Vector3(15.0f, 15.0f, 10.0f), Vector3(0.0f, 90.0f, 0.0f));
        CreateMeshObject("ConRail", Vector3(20.0f, 15.0f, 10.0f), Vector3(0.0f, 90.0f, 0.0f));
        CreateMeshObject("ConRail", Vector3(25.0f, 15.0f, 10.0f), Vector3(0.0f, 90.0f, 0.0f));
       
    
       


        CreateMeshObject("ConBlock", Vector3(30.0f, 5.0f, 10.0f), Vector3(0.0f));
        CreateMeshObject("ConBlock", Vector3(30.0f, 0.0f, 10.0f), Vector3(0.0f));

        CreateMeshObject("ConBlock", Vector3(30.0f, 5.0f, 15.0f), Vector3(0.0f));
        CreateMeshObject("ConBlock", Vector3(30.0f, 0.0f, 15.0f), Vector3(0.0f));

        CreateMeshObject("ConBlock", Vector3(30.0f, 0.0f, 20.0f), Vector3(0.0f));
        CreateMeshObject("ConBlock", Vector3(30.0f, 0.0f, 25.0f), Vector3(0.0f));
        CreateMeshObject("ConBlock", Vector3(30.0f, 0.0f, 25.0f), Vector3(0.0f));
        CreateMeshObject("Floor", Vector3(30.0f, 5.01f, 5.0f), Vector3(0.0f));


        CreateMeshObject("ConStair", Vector3(25.0f, 10.0f, 15.0f), Vector3(0.0f,-90.0f,0.0f));
        CreateMeshObject("ConStair", Vector3(25.0f, 5.0f, 20.0f), Vector3(0.0f,-90.0f,0.0f));

        CreateMeshObject("ConRail", Vector3(30.0f, 5.0f, 25.0f), Vector3(0.0f, 0.0f, 0.0f));
        CreateMeshObject("ConRail", Vector3(30.0f, 5.0f, 25.0f), Vector3(0.0f, 90.0f, 0.0f));

        
        CreateMeshObject("ConStair", Vector3(20.0f, 0.0f, 20.0f), Vector3(0.0f, 180.0f, 0.0f));



        // Door creation

        CreateMeshObject("DoorFrame", Vector3(-19.55f, 15.0f, 5.0f), Vector3(0.0f, 90.0f, 0.0f));
        CreateMeshObject("Door", Vector3(-19.70f, 15.0f, 8.55f), Vector3(0.0f, 90.0f, 0.0f));

    }


    void BuildScene()
    {
// Floooor and ceiling

        
        BuildFloorCeling();

        BuildWalls();

        BuildWAlkwayStairs();

        // teh satelllite
        CreateMeshObject("Satellite", Vector3(-3.0f, 0.0f, -10.0f ), Vector3(0.0f, 25.0f,0.0f));


        // Rocket boii!!!
        CreateMeshObject("Rocket", Vector3(22.5f, 0.0f, -15.0f), Vector3(0.0f));

        // Finally the Shuttle
        CreateMeshObject("Shuttle", Vector3(0.0f, 0.0f, 15.0f), Vector3(0.0,180.0f,0.0f));

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






