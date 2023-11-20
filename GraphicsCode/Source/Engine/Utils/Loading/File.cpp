#include "File.h"
#include <sstream>
#include <map>
#include "Engine/Utils/Logging/Log.h"

namespace FanshaweGameEngine
{
#define ROOTPATH = ".."

	std::map<int, int> FileModeTable =
	{
		{ File::READ, std::fstream::in},
		{ File::WRITE, std::fstream::out},
		{ File::BINARY, std::fstream::binary},
		{ File::READ | File::BINARY, std::fstream::in | std::fstream::binary },
		{ File::WRITE | File::BINARY, std::fstream::out | std::fstream::binary },
		{ File::READ | File::WRITE, std::fstream::in | std::fstream::out },
		{ File::READ | File::WRITE | File::BINARY, std::fstream::in | std::fstream::out | std::fstream::binary }
	};



	File::File(const FilePath& path, int mode)
	{
		Open(path, mode);
	}

	File::File(const std::string& path, int mode)
	{
		Open(path, mode);
	}

	FileStream& File::GetStream()
	{
		return m_fileStream;
	}

	bool File::IsOpen() const
	{
		return m_fileStream.is_open() && m_fileStream.good();
	}

	void File::Open(FilePath path, int mode)
	{
		m_filePath = std::move(path);

		if (!File::Exists(m_filePath))
		{
			if ((mode & File::WRITE) == 0)
			{
				LOG_ERROR("File : file not found [{0}]", m_filePath.string());
				return;
			}
			else
			{
				FilePath directory = m_filePath.parent_path();
				if (!directory.empty() && !File::Exists(directory))
				{
					File::CreateDir(directory);
				}
			}
		}

		if (IsOpen()) { Close(); }
		m_fileStream.open(m_filePath, (std::ios_base::openmode)FileModeTable[mode]);

	}

	void File::Open(const std::string& path, int mode)
	{
		FilePath filepath = path.c_str();
		Open(std::move(filepath), mode);
	}

	void File::Close()
	{
		m_fileStream.close();
	}

	void File::WriteBytes(const uint8_t* bytes, size_t size)
	{
		m_fileStream.write((const char*)bytes, size);
	}

	void File::ReadBytes(uint8_t* bytes, size_t size)
	{
		m_fileStream.read((char*)bytes, size);
	}

	FilePath File::GetFilePathfromString(const std::string& stringPath)
	{
		// making sure the encoding is correct, otherwise the path points to the wrong file in rare cases
		return std::filesystem::u8path(stringPath);
	}

	bool File::Exists(const FilePath& path)
	{
		return std::filesystem::exists(path);
	}

	bool File::Exists(const std::string& stringPath)
	{
		return std::filesystem::exists(GetFilePathfromString(stringPath));
	}


	std::string File::ReadFileToString(const FilePath& path)
	{
		// Checking if the File exists, otherwise returning a null string
		if (!Exists(path))
		{
			return std::string();
		}

		
		// Opening a string stream
		std::ifstream stream(path);

		// Creating a buffer to store the data
		std::stringstream buffer;

		// Storing the stream data into the buffer line by line
		buffer << stream.rdbuf();

		// done with the file, so closing
		stream.close();

		

		// Outputting buffer data in form of a string
		return buffer.str();


	}

	
	
	// Get the file name without the extention
	std::string File::GetFileName(const FilePath& path)
	{
		return path.stem().string();
	}

	std::string File::GetFileNameWithExt(const FilePath& path)
	{
		return path.filename().string();
	}

	bool File::WriteFileToText(const FilePath& path, const std::string& text)
	{
		std::ofstream stream(path, std::ios::binary | std::ios::trunc);

		if (!stream)
		{
			stream.close();
			return false;
		}

		stream.write((char*)&text[0], (uint32_t)text.size());
		stream.close();


		return true;
	}

	FilePath File::GetCurrentPath()
	{
		return std::filesystem::current_path();
	}

	FilePath File::GetEngineDir()
	{
		return GetCurrentPath() /= "Engine\\";
	}

	FilePath File::GetShaderDir()
	{
		return GetEngineDir() /= "Shaders\\";
	}


	void File::CreateDir(const FilePath& path)
	{
		if (!File::Exists(path))
		{
			std::filesystem::create_directory(path);
		}
	}

	void File::CreateDir(const std::string& path)
	{
		if (!File::Exists(path))
		{
			std::filesystem::create_directory(path.c_str());
		}
	}

}
