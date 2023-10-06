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
    
      
      

       // Loading a new Resource from the Disk and storing the reference in the Model lirary for future use
       SharedPtr<Model> model = GetModelLibrary()->LoadModel("Bathtub", "Assets\\bathtub.ply");
       CHECKNULL(model);


       //SharedPtr<GameObject> bathObject;
       // ============= CREATING OBJECTS FROM DATA ======================
      // bathObject = GetObjectLibrary()->CreateObject(model->GetMeshes().data()[0], "BathObject");
      // CHECKNULL(bathObject);

       //Factory<GameObject>::Create(model->GetMeshes().data()[0]);

       //bathObject->AttachShader(GetShaderLibrary()->GetResource("StandardShader"));

       // Setting Positional Data
       
       //bathObject->m_transform.SetPosition(Vector3(1.0f, 5.0f, 2.0f));

       
   }






};


int main(int argc, char* argv)
{
    // Creating a new Appinstance
    GameApplication* app = new GameApplication();

    FilePath path = File::GetCurrentPath();

    // Always Initialize the App
    app->Initialize();
    // Running the Application
    app->Run();
}