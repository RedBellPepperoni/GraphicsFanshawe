#include "GameEngine.h"




class GameApplication : public Application
{
    
   void OnInit()
   {
       
       LOG_CRITICAL("This is a CRITICAL Log message");
       LOG_ERROR("This is a ERROR Log message");
       LOG_WARN("This is a WARN Log message");
       LOG_INFO("This is a INFO Log message");
       LOG_TRACE("This is a TRACE Log message");
    
      

       // Create a new Camera
       SharedPtr<Camera> mainCamera = Factory<Camera>::Create();

       // Set the position
       mainCamera->m_transform.SetPosition(Vector3(20.0f, 30.0f, 30.0f));
       mainCamera->SetDirection(-mainCamera->m_transform.GetPosition());

       // Add the created camera to teh Scene List
       m_scenecameras.push_back(mainCamera);


      

       // Loading a new Resource from the Disk and storing the reference in the Model lirary for future use
       SharedPtr<Model> model = GetModelLibrary()->LoadModel("Bathtub", "Assets\\bathtub.ply");
       CHECKNULL(model);

       SharedPtr<Model> spheremodel = GetModelLibrary()->LoadModel("IcoSphere", "Assets\\icosphere.ply");
       CHECKNULL(spheremodel);



       SharedPtr<GameObject> bathObject;
       SharedPtr<GameObject> sphereObject;


       // ============= CREATING OBJECTS FROM DATA ======================
       bathObject = GetObjectLibrary()->CreateObject(model->GetMeshes().data()[0], "BathObject");
       CHECKNULL(bathObject);

       // Creating a New Material
       SharedPtr<Material> bathMat = GetRenderManager()->GetMaterialLibrary()->CreateMaterial("BathMat");


       sphereObject = GetObjectLibrary()->CreateObject(spheremodel->GetMeshes().data()[0], "SphereObject01");
       CHECKNULL(sphereObject);



       bathObject->m_material = bathMat;
       // Setting Positional Data    
       bathObject->m_transform.SetPosition(Vector3(0.0f, 0.0f, 0.0f));

       sphereObject->m_material = bathMat;
       sphereObject->m_transform.SetPosition(Vector3(0.0f, 10.0f, 10.0f));

       sphereObject = GetObjectLibrary()->CreateObject(spheremodel->GetMeshes().data()[0], "SphereObject02");
       CHECKNULL(sphereObject);

       sphereObject->m_material = bathMat;
       sphereObject->m_transform.SetPosition(Vector3(0.0f, 10.0f, 15.0f));


       sphereObject = GetObjectLibrary()->CreateObject(spheremodel->GetMeshes().data()[0], "SphereObject03");
       CHECKNULL(sphereObject);

       sphereObject->m_material = bathMat;
       sphereObject->m_transform.SetPosition(Vector3(0.0f, 10.0f, 20.0f));

       // Telling t
       mainCamera->SetDirection(sphereObject->m_transform.GetPosition()  - mainCamera->m_transform.GetPosition());
       
   }






};


int main(int argc, char* argv)
{
    // Creating a new Appinstance
    GameApplication* app = new GameApplication();

    //FilePath path = File::GetCurrentPath();

    // Always Initialize the App
    app->Initialize();
    // Running the Application
    app->Run();
}