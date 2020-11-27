#pragma once
#include <vulkan/vulkan.hpp>

#include "vkII_types.h"

namespace vkII {
	
	struct image_stats
	{
		float stddev;
		float mean;
		float avg;
		float max;
		float min;

	};


	class Image
	{
	public:
		Image(vk::Image img, bool no_copy = false);
		Image(int h, int w, vk::Format fmt = vk::Format::eR32Sfloat);
		
		vkII::DataLocation getLocation();

		vk::Result moveToDevice();

		vk::Result moveToHost();
		
		~Image();
	private:
		float * data;
		vk::Image* img;
		vk::ImageCreateInfo imageInfo;
		DataLocation dataLoc = eHOST;

	};

}

