#pragma once
#include "Engine/Utils/Loading/File.h"


namespace FanshaweGameEngine
{
	class Image;


	enum class ImageType
	{
		PNG,
		BMP,
		JPG,
		TGA,
		HDR
	};

	class ImageManager
	{
	public:

		static void SaveImage(const FilePath& filePath, const Image& image, ImageType type);
		static void SaveImage(const std::string& filePath, const Image& image, ImageType type);
		
		
	// Can Add texture saving here

		// Also can add taking screenshots
	
	
	};
}

