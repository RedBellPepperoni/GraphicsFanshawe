#include "GameEngine.h"




class GraphicApp : public Application
{

    void OnInit()
    {

        LOG_CRITICAL("This is a CRITICAL Log message");
        LOG_ERROR("This is a ERROR Log message");
        LOG_WARN("This is a WARN Log message");
        LOG_INFO("This is a INFO Log message");
        LOG_TRACE("This is a TRACE Log message");






        //  Entity mainCamera = GetCurrentScene()->CreateEntity("Camera01");
        //  mainCamera.AddComponent<Camera>();
        //  mainCamera.AddComponent<Transform>();

        //  // Set the position
        ////mainCamera->m_transform.SetPosition(Vector3(20.0f, 30.0f, 30.0f));
        ////mainCamera->SetDirection(-mainCamera->m_transform.GetPosition());

        //  SetMainCameraIndex(0);

        //  Transform& cameraTransform = mainCamera.GetComponent<Transform>();

        //  cameraTransform.SetPosition(Vector3(20.0f, 30.0f, 30.0f));


       /*   Vector3 position = cameraTransform.GetPosition();

          mainCamera.GetComponent<Camera>().SetDirection(-cameraTransform.GetPosition());*/




          // Loading a new Resource from the Disk and storing the reference in the Model lirary for future use
        SharedPtr<Model> model = GetModelLibrary()->LoadModel("Bathtub", "Assets\\bathtub.ply");
        CHECKNULL(model);

        SharedPtr<Model> spheremodel = GetModelLibrary()->LoadModel("IcoSphere", "Assets\\icosphere.ply");
        CHECKNULL(spheremodel);



        // SharedPtr<GameObject> bathObject;
         //SharedPtr<GameObject> sphereObject;

         // Using ECS now
        Entity bathObject = GetCurrentScene()->CreateEntity("BathObject");
        Entity sphereObject = GetCurrentScene()->CreateEntity("sphere_01");



        // Add a Trasnform. later make sure every spawnd entity has an auto attached transform
        bathObject.AddComponent<Transform>();
        bathObject.GetComponent<Transform>().SetPosition(Vector3(0.0f));
        bathObject.GetComponent<Transform>().SetRotation(Vector3(0.0f, 0.0f, 0.0f));

        // Set the First mesh reference as out mesh component
        // Later need to make this automatically generate entities for multiple meshes
        bathObject.AddComponent<MeshComponent>(model->GetMeshes()[0]);


        bathObject.AddComponent<MeshRenderer>();





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