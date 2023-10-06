#include "ResourceManager.h"
#include "Engine/Core/Rendering/Shader/Shader.h"
#include "Engine/Utils/Loading/Model.h"


namespace FanshaweGameEngine
{
	
    SharedPtr<Shader> ShaderLibrary::LoadShader(const std::string& friendlyName,const std::string& vertexSource,const std::string& fragmentSource)
	{
		// Making a new Shader pointer ref
		SharedPtr<Shader> newShader = Factory<Shader>::Create();

		// Loading the Shader and creating and compiling a GL Shader
		if (newShader->Load(vertexSource, fragmentSource))
		{
			
			// adding to the Resource Map
			CreateResource(friendlyName, newShader);
			// Retruning the newly created and compiled shader
			return newShader;

		}

		// A very rare case , but reseting it before deleting is essential 
		newShader.reset();

		//
		return nullptr;
		
	}


	SharedPtr<Model> ModelLibrary::LoadModel(const std::string& friendlyName, const std::string& modelpath)
	{
		SharedPtr<Model> newModel = Factory<Model>::Create("Assets\\bathtub.ply");

		// Model was loaded successfully
		if (newModel != nullptr)
		{
			CreateResource(friendlyName, newModel);
		}

		// Returning the model if created successfuly , nullptr otherwise
		return newModel;
	}



}
