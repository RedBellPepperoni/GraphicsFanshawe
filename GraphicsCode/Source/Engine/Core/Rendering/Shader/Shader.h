#pragma once
#include "Engine/Utils/Math.h"
#include <vector>
#include <string>
#include <unordered_map>

#include "Engine/Utils/Loading/File.h"



namespace FanshaweGameEngine
{

	


	namespace Rendering
	{
		struct ShaderSubInfo;
		

		class Shader
		{

		public:

			// The type of Shader to load
			enum ShaderType
			{ 
				VERTEX,				// 1 
				GEOMETRY,			// 2
				FRAGMENT,			// 3

				UNKNOWN // This also defines the total number of Shadertypes
			};


			using UniformMap = std::unordered_map<std::string, uint32_t>;

			class ShaderProgram
			{

			public:

				// Constructor
				ShaderProgram(uint32_t shaderId);

				// Get the GL location from the uniform name
				int GetUniformLocation(std::string uniformName);

			private:

				// Storage to contain all the uniform needed for a particular shader
				UniformMap m_uniformData;

				// Id of the Shader
				uint32_t m_shaderId;

			};



		private:

			// The bound ID for the shader
			uint32_t m_Id;
			ShaderProgram m_program;


			void DeleteProgram();
			void SetProgramID(uint32_t newId);

			//bool CheckShaderError(uint32_t programId, uint32_t errorStage);
			
			static uint32_t CreateShader(int glType, std::string& source, FilePath& path);

			//bool CompileShaderFromSource(ShaderSubInfo& info);

		public:

			Shader();
			~Shader();

			
			// ====================== STATIC STUFF ===============================	

			
			// Loads all the shader types for a particular shaderprogram
			uint32_t CreateShaderProgram(uint32_t* shaderIds, const ShaderSubInfo* shaderTypes, size_t shaderCount);

			uint32_t GetProgramId() const;

			// ===================== SHADER STUFF =================================

			bool Load(const std::string& vertPath, const std::string& fragPath);
			void Load(const std::string& vertPath, const std::string& geoPath, const std::string& fragPath);


		};



		
	}
}


