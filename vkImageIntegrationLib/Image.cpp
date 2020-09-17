#include "Image.h"

namespace vkII {
	vkII::Image::Image(vk::Image img, bool no_copy)
	{
	}

	vkII::Image::Image(int h, int w, vk::Format fmt)
	{
#if	defined(_DEBUG)
		assert(fmt == vk::Format::eR32Sfloat);
		if (fmt != vk::Format::eR32Sfloat)
		{
			//assert
		}
#endif

		vk::ImageCreateInfo imageInfo;
		imageInfo.imageType = vk::ImageType::e2D;
		imageInfo.mipLevels = 0;
		imageInfo.extent.depth = 1;
		imageInfo.extent.height = h;
		imageInfo.extent.width = w;
		imageInfo.tiling = vk::ImageTiling::eOptimal;
		imageInfo.sharingMode = vk::SharingMode::eExclusive;

	}

	vkII::DataLocation vkII::Image::getLocation()
	{
		return this->dataLoc;
	}

	vk::Result vkII::Image::moveToDevice()
	{
		this->dataLoc = DataLocation::eDEVICE;
		return vk::Result();
	}

	vk::Result vkII::Image::moveToHost()
	{
		this->dataLoc = DataLocation::eHOST;
		return vk::Result();
	}
}