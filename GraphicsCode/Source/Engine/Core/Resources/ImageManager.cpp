#include "ImageManager.h"

namespace FanshaweGameEngine
{
	void ImageManager::SaveImage(const FilePath& filePath, const Image& image, ImageType type)
	{
		ImageManager::SaveImage(filePath.string(), image, type);
	}

	void ImageManager::SaveImage(const std::string& filePath, const Image& image, ImageType type)
	{
		File file(filePath, File::READ | File::BINARY);

	}

	
}