#pragma once
#include <vulkan/vulkan.hpp>

#include "Image.h"

namespace vkII {
	class vkImageIntegration
	{
	public:
		vkImageIntegration(vk::Device device, vk::Queue queue);
		~vkImageIntegration();

	private:
		vk::Device dev;
		vk::Queue q;
	};

}