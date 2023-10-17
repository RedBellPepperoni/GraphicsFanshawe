#include "ResourceManager.h"
#include "Engine/Core/Rendering/Shader/Shader.h"
#include "Engine/Utils/Loading/Model.h"
#include "Engine/Core/Rendering/Essentials/Material.h"
#include "Engine/Utils/Logging/Log.h"


namespace FanshaweGameEngine
{
	
	


    SharedPtr<Shader> ShaderLibrary::LoadShader(const std::string& friendlyName,const std::string& vertexSource,const std::string& fragmentSource)
	{

		std::string path = File::GetCurrentPath().string();

		LOG_WARN("DEafultPath : {0}",path);


		// Making a new Shader pointer ref
		SharedPtr<Shader> newShader = Factory<Shader>::Create();

		// Loading the Shader and creating and compiling a GL Shader
		if (newShader->Load(vertexSource, fragmentSource))
		{
			
			// adding to the Resource Map
			ShaderLibrary::CreateResource(friendlyName, newShader);
			// Retruning the newly created and compiled shader
			return newShader;

		}

		// A very rare case , but reseting it before deleting is essential 
		//newShader.reset();

		LOG_INFO("ShaderLibrary : Loaded [{0}]", friendlyName);

		//
		return nullptr;
		
	}


	SharedPtr<Model> ModelLibrary::LoadModel(const std::string& friendlyName, const std::string& modelpath)
	{
		SharedPtr<Model> newModel = Factory<Model>::Create(modelpath);

		// Model was loaded successfully
		if (newModel != nullptr)
		{
			ModelLibrary::CreateResource(friendlyName, newModel);
		}

		LOG_INFO("ModelLibrary : Loaded [{0}] from path  [{1}]", friendlyName, modelpath);

		// Returning the model if created successfuly , nullptr otherwise
		return newModel;
	}



	SharedPtr<Material> MaterialLibrary::CreateMaterial(const std::string& friendlyName)
	{
		SharedPtr<Material> newMaterial = Factory<Material>::Create();

		if (newMaterial != nullptr)
		{
			MaterialLibrary::CreateResource(friendlyName, newMaterial);
		}

		return newMaterial;
	}

}
