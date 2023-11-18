#pragma once
#include "Engine/Utils/Loading/File.h"
#include "Engine/Core/Rendering/Definitions.h"


namespace FanshaweGameEngine
{

	/*
		A Model is defined as an external Object loaded from the disk :
		it should contain Vertex , index information

	*/

	using namespace Rendering;
	using namespace std;


	struct MaterialDetails
	{
		std::string name;

		// The file path for the diffuse/Albedo texture
		FilePath albedoMap;

		// The file path for the normal texture
		FilePath normalMap;

		FilePath emissionMap;

		FilePath heightMap;

		// The file path for the combined maps
		FilePath metalicRoughAOMap;

		bool alphaMask = false;

		float transparency = 0.0f;

		float emission = 0.0f;

		Vector3 baseColor = Vector3(1.0f);

		Vector2 uvMultiplier = Vector2(1.0f);

		float metalness = 0.0f;
		float roughness = 0.0f;
	};

	// FlagEnum
	enum ModelDetailMode
	{
		none = 0, // Binary 0000
		color = 1 << 0, // Binary 0001
		normal = 1 << 1, // Binary 0010
	};

	struct MeshDetails
	{
		std::string name;

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		MaterialDetails* material = nullptr;

		bool useTexture = false;

		bool useNormal = false;

		// Add Texture and material Details here
	};



	struct ModelDetail
	{
		// All the Submeshes
		std::vector<MeshDetails> meshes;

		// Add materials list here 

		std::vector<MaterialDetails> materials;
	};


	// This is a helper class to help load Model data using Assimp.
	// Currently only raw model loading is implemented
	// ----------> TODO: Implement Material and texture loading for each model <---------------
	class ModelLoader
	{


	public:

		// Constructor
		ModelLoader();

		// Destructor
		~ModelLoader();

		// Function to implement when assimp is used : right now ignore
		static ModelDetail LoadModel(const FilePath& filePath);

		// Loaded Function to use string paths
		static ModelDetail LoadModel(const string& stringPath);

		// Function related to loading ply models provided in Graphics-1
		// Updated this function to auto load normal info and color info if it detects that particular data
		// TODO : use assimp to deal with all type of meshes
		static ModelDetail LoadPlyModel(const FilePath& filePath);

		// Loaded Function to use string paths
		//static ModelDetail LoadPlyModel(const string& stringPath);


		//static std::vector<MaterialDetails> LoadMaterials(const FilePath& path);


	};
}

