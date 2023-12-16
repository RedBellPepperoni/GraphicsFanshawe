#include "Model.h"
#include "Engine/Core/Application/Application.h"

namespace FanshaweGameEngine
{
    Model::Model(const FilePath& filepath)
    {
        Load(filepath);
       
    }

    std::vector<SharedPtr<Mesh>>& Model::GetMeshes()
    {
        return m_meshes;
    }

    SharedPtr<Mesh>& Model::GetFirstMesh()
    {
        return m_meshes[0];
    }

    void Model::Load(const FilePath& filepath)
    {
        // fetching the model details from the given filepath
        ModelDetail loadedmodelDetail = ModelLoader::LoadModel(filepath);

        int meshCount = 0;

        // Incase there are sub meshes we generate a mesh for each of them
        for (MeshDetails meshDetail : loadedmodelDetail.meshes)
        {

            // Creating a new Mesh from the gathered data
            SharedPtr<Mesh> newMesh = MakeShared<Mesh>(meshDetail.vertices, meshDetail.indices);
            newMesh->SetName(File::GetFileName(filepath) + std::to_string(meshCount));


            // Adding the generated mesh to the Model List of meshes
            m_meshes.push_back(newMesh);

            meshCount++;
        }
       

        
    }
}