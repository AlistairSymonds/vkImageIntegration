#pragma once
#include <vulkan/vulkan.hpp>

namespace vkII {
	class vkImageIntegration
	{
	public:
		vkImageIntegration(vk::Device device);
		~vkImageIntegration();

	private:
		vk::Device dev;
	};

}