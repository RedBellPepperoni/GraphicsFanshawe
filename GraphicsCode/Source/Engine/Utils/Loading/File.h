#pragma once
#include <filesystem>
#include <fstream>

namespace FanshaweGameEngine
{

	// Ask Mr Feeney if using C++17 is allowed for std::filesystem ----->  allowed by Mr Feeney
	using FilePath = std::filesystem::path;


	// Wrapper around the std file system
	class File
	{

	public:

		static FilePath GetFilePathfromString(const std::string& stringPath);

		// Check if a file exists at the given path
		static bool Exists(const FilePath& path);

		static bool Exists(const std::string& stringPath);


		// Get data from the file at the context path as a string
		static std::string ReadFileToString(const FilePath& path);



		static std::string GetFileName(const FilePath& path);
		static std::string GetFileNameWithExt(const FilePath& path);

		// Write given string to a Text file
		static bool WriteFileToText(const FilePath& path, const std::string& text);

		static FilePath GetCurrentPath();

	};
}

