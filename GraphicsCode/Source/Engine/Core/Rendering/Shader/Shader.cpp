#include "Shader.h"
#include "Engine/Utils/GLUtils.h"
#include "Engine/Utils/Logging/Log.h"

namespace FanshaweGameEngine
{
	namespace Rendering
	{

		struct ShaderSubInfo
		{
			Shader::ShaderType type;
			std::string source;
			FilePath path;
		};

		// getting native 
		inline static int GetGLShaderType(Shader::ShaderType type) 
		{
			switch (type)
			{
			case FanshaweGameEngine::Rendering::Shader::VERTEX: return GL_VERTEX_SHADER;
				break;
			case FanshaweGameEngine::Rendering::Shader::GEOMETRY: return GL_GEOMETRY_SHADER;
				break;
			case FanshaweGameEngine::Rendering::Shader::FRAGMENT: return GL_FRAGMENT_SHADER;
				break;
			case FanshaweGameEngine::Rendering::Shader::UNKNOWN: return GL_FALSE;
				break;
			default: return GL_FALSE;
				break;
			}
		}


		// Shader Program Function Implementation

		Shader::ShaderProgram::ShaderProgram(uint32_t shaderId)
			: m_shaderId(shaderId)
		{
		}

		int Shader::ShaderProgram::GetUniformLocation(std::string uniformName)
		{
			typename UniformMap::iterator itr = m_uniformData.find(uniformName);

			if (itr != m_uniformData.end())
			{
				return itr->second;
			}

			uint32_t location = glGetUniformLocation(m_shaderId, uniformName.c_str());

			if (location == -1)
			{
				LOG_ERROR("{0} : Uniform not found", uniformName);
				
			}
			
			m_uniformData[uniformName] = location;

			return location;
		}



		// Shader  Function Implementaion
		
		void Shader::DeleteProgram()
		{
			if (m_Id != 0)
			{
				//deleted shader program with id 
				glDeleteProgram(m_Id);
			}
			
			m_Id = 0;
		}

		Shader::Shader()
			: m_Id(0), m_program(m_Id)
		{
		}

		Shader::~Shader()
		{
			DeleteProgram();
		}

		void Shader::SetProgramID(uint32_t newId)
		{
			DeleteProgram();

			m_Id = newId;

			m_program = ShaderProgram{ newId };

		}

		
		uint32_t Shader::CreateShaderProgram(uint32_t* shaderIds, const ShaderSubInfo* info, size_t shaderCount)
		{
			// Storing a new Id for the shader for each of the compiled shader types
			for (size_t iterator = 0; iterator < shaderCount; iterator++)
			{
				ShaderSubInfo subInfo = info[iterator];
				shaderIds[iterator] = CreateShader(GetGLShaderType(subInfo.type), subInfo.source, subInfo.path);
			}

			// Creating the  Shader Program
			GLDEBUG(uint32_t program = glCreateProgram());

			// Attaching each of the sub shader to the program ID
			for (size_t iterator = 0; iterator < shaderCount; iterator++)
			{
				GLDEBUG(glAttachShader(program, shaderIds[iterator]));
			}

			// Linking the program
			GLDEBUG(glLinkProgram(program));








			return 0;
		}

		// Just to make sure the correct Filepath is used
		
		uint32_t Shader::CreateShader(int glType, std::string& source, FilePath& path)
		{
			uint32_t shaderId;
			GLDEBUG(shaderId = glCreateShader((GLenum)glType));	

			const char* processedShaderCodePtr = source.c_str();

			
			GLDEBUG(glShaderSource(shaderId, 1, &processedShaderCodePtr, nullptr));
	
			GLDEBUG(glCompileShader(shaderId));

			return shaderId;
		}

		/*bool Shader::GetShaderError(uint32_t programId, uint32_t errorStage)
		{
			return false;
		}*/

		



		bool Shader::Load(const std::string& vertPath, const std::string& fragPath)
		{
			// Setting vertex and fragment data
			std::array<ShaderSubInfo , 2> subInfo =
			{
				ShaderSubInfo
				{	// Defining the type
					ShaderType::VERTEX,
					// Pulling the Shader vertex data into a continuos string
					File::ReadFileToString(vertPath),
					// Storing the path
					File::GetFilePathfromString(vertPath)
				},
				ShaderSubInfo
				{
					// Defining the typr
					ShaderType::FRAGMENT,
					// Pulling the Shader fragment data into a continuos string
					File::ReadFileToString(fragPath),
					// Storing the path
					File::GetFilePathfromString(fragPath)
				}
			};

			const size_t subShaderCount = subInfo.size();

			// Creating a container to store the compiled sub shaders
			std::array<uint32_t, subShaderCount> subShaders;

			// Generating a program id from the given sub shader infos
			uint32_t glProgram = CreateShaderProgram(subShaders.data(), subInfo.data(), subShaderCount);


			SetProgramID(glProgram);

			return true;

		}

		uint32_t Shader::GetProgramId() const
		{
			return m_Id;
		}

		void Shader::Load(const std::string& vertPath, const std::string& fragPath, const std::string& geoPath)
		{

			// Implement the loading for vert frag and geomerty shader here
		}

		

		




	}
}
