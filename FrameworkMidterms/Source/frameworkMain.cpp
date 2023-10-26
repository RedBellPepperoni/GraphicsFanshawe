
// The actual engine
#include "GameEngine.h"

// The custom clases for this applicaiton
#include"Framework/Board/Board.h"


class FrameworkApp : public Application
{
   


private:

    Framework::Board m_board;


public:




    void OnInit()
    {
        LOG_CRITICAL("This is a CRITICAL Log message");
        LOG_ERROR("This is a ERROR Log message");
        LOG_WARN("This is a WARN Log message");
        LOG_INFO("This is a INFO Log message");
        LOG_TRACE("This is a TRACE Log message");



          // Loading a new Resource from the Disk and storing the reference in the Model lirary for future use
        SharedPtr<Model> model = GetModelLibrary()->LoadModel("Board", "Assets\\Berzerk_Level_Ouput.ply");
        CHECKNULL(model);

       /* SharedPtr<Model> spheremodel = GetModelLibrary()->LoadModel("IcoSphere", "Assets\\icosphere.ply");
        CHECKNULL(spheremodel);
*/


        // SharedPtr<GameObject> bathObject;
         //SharedPtr<GameObject> sphereObject;

         // Using ECS now
        Entity boardObject = GetCurrentScene()->CreateEntity("BathObject");
       // Entity sphereObject = GetCurrentScene()->CreateEntity("sphere_01");



        // Add a Trasnform. later make sure every spawnd entity has an auto attached transform
        boardObject.AddComponent<Transform>();
        boardObject.GetComponent<Transform>().SetPosition(Vector3(0.0f));

        // Making the board flat with the ground
        boardObject.GetComponent<Transform>().SetRotation(Quaternion(Vector3(glm::radians(90.0f), 0.0f, 0.0f)));

        // Set the First mesh reference as out mesh component
        // Later need to make this automatically generate entities for multiple meshes
        boardObject.AddComponent<MeshComponent>(model->GetMeshes()[0]);
        boardObject.AddComponent<MeshRenderer>();


        m_board.GenerateBoardfromTextFile("Assets\\Berzerk_Level_1193265.txt");

        std::vector<Framework::CellData> grid =  m_board.GetGrid();

    }

    void OnUpdate(float deltaTime)
    {

    }
};



int main(int argc, char* argv)
{
    UniquePtr<FrameworkApp> app = MakeUnique<FrameworkApp>();

    app->Initialize();

    app->Run();

}