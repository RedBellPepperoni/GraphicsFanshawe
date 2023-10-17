#include "ModelLoader.h"
#include <iostream>
#include <sstream>

namespace FanshaweGameEngine
{
    ModelLoader::ModelLoader()
    {
    }

    ModelLoader::~ModelLoader()
    {
    }

    ModelDetail ModelLoader::LoadModel(const FilePath& filePath)
    {
        // Creating a New ModelDetails Ref
        ModelDetail model;

        // File doesnt exist at the given path
        if (!File::Exists(filePath))
        {
            // Add Logger Here
            return model;
        }

        // File Exists, we continue forward

        model = LoadPlyModel(filePath);


        return model;
    }

    ModelDetail ModelLoader::LoadModel(const string& stringPath)
    {
        return LoadModel(File::GetFilePathfromString(stringPath));
    }


    ModelDetail ModelLoader::LoadPlyModel(const FilePath& filePath)
    {
        // Creating a New ModelDetails Ref
        ModelDetail model;

        MeshDetails mesh;

        // Assuming the file is in ASCII
        // Loading the entire file to a tempstring
        std::string tempFile = File::ReadFileToString(filePath);

        if (tempFile.empty())
        {
            // Model not loaded
            return model;
        }

        // Need to figure out how to deal with multiple meshes with the same name
        // Setting the name of mesh
        mesh.name = File::GetFileName(filePath);

       // std::cout << "Loading Model : " << File::GetFileNameWithExt(filePath) << std::endl;

        // Initializing the string stream with the loaded Text data
        std::istringstream stringStream(tempFile);


        std::string key;
        uint32_t vertexCount = 0;
        uint32_t faceCount = 0;

        uint32_t additionalVertexData = 0;

        // Read line by line to find the number of vertices
        do
        {
            stringStream >> key;

            if (key == "vertex")
            {
                // the key after "vertex" should be an int and should be the total number of vertex data in the file
                stringStream >> vertexCount;
            }

            else if (key == "nz")
            {
                // Found vertex normal data
                additionalVertexData = ModelDetailMode::normal;

               // std::cout << "Found Normal Data" << std::endl;
            }

            else if (key == "alpha")
            {
                // Found vertex color data
                additionalVertexData |= ModelDetailMode::color;

                //std::cout << "Found Color Data" << std::endl;
            }



            else if (key == "face")
            {
                // the key after "face" should be an int and should be the total number of triangles in the file
                stringStream >> faceCount;

            }

            else if (key == "end_header")
            {
                // End of header data, now the actual vertex and index data starts
                break;
            }

        } while (stringStream);


        // Assuming there is only one mesh per file (for now)

        // =============================== Loading Vertex data from the file ==================================
        Vertex tempVert;

        for (uint32_t index = 0; index < vertexCount; index++)
        {
            // All models should have vertex data

            // Storing each vertex data
            stringStream >> tempVert.position.x;
            stringStream >> tempVert.position.y;
            stringStream >> tempVert.position.z;


            /*  std::string PrintData = "VertexData" + std::to_string(tempVert.position.x)
                  + " " + std::to_string(tempVert.position.y)
                  + " " + std::to_string(tempVert.position.z);*/

                  // Checking if we should include color data
        

            // Checking if we should include vertex normal data
            if (additionalVertexData & ModelDetailMode::normal)
            {
                // If normal data is detected, we add that to our structure
                stringStream >> tempVert.normal.x;
                stringStream >> tempVert.normal.y;
                stringStream >> tempVert.normal.z;

                // PrintData += " " + std::to_string(tempVert.normal.x) + " " + std::to_string(tempVert.normal.y) + " " + std::to_string(tempVert.normal.z);
            }


            if (additionalVertexData & ModelDetailMode::color)
            {
                // If color data is detected, we add that to our structure
                stringStream >> tempVert.color.r;   tempVert.color.r /= 255.0f;
                stringStream >> tempVert.color.g;   tempVert.color.g /= 255.0f;
                stringStream >> tempVert.color.b;   tempVert.color.b /= 255.0f; 
                stringStream >> tempVert.color.a;   tempVert.color.a /= 255.0f;

                // PrintData += " " + std::to_string(tempVert.color.r) + " " + std::to_string(tempVert.color.g) + " " + std::to_string(tempVert.color.b);
            }

            /*  std::cout << PrintData
                  << std::endl;*/


                  // Storing the finalized vertex data for the first mesh 
            mesh.vertices.push_back(tempVert);

        }


        // =============================== Loading Index Data from the File =====================================

        // Defining Temporary data storage
        uint32_t tempIndex, numIndexperFace;

        // iterating through all the faces to gather index data
        for (uint32_t index = 0; index < faceCount; index++)
        {
            // Getting how many indices are in that face
            stringStream >> numIndexperFace;


            // Storing Each index found 
            for (uint32_t indice = 0; indice < numIndexperFace; indice++)
            {
                stringStream >> tempIndex;
                mesh.indices.push_back(tempIndex);
            }


        }


        //std::cout << "Model Loaded Successfully -> total vertices : " << vertexCount << " total faces : " << faceCount << std::endl;

        model.meshes.push_back(mesh);

        return model;
    }


    
}

