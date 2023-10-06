#include "File.h"
#include <sstream>


namespace FanshaweGameEngine
{
#define ROOTPATH = ".."



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
}
