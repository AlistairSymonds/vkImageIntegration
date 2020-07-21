#pragma once
#include<vulkan/vulkan.hpp>

namespace vkII {

	typedef struct capabilitiesNeeded {
		bool hasComputeQueue;
	} capabilitiesNeeded;


	bool validateDeivce(vk::Device device);

	capabilitiesNeeded checkDeivce(vk::Device device);
}