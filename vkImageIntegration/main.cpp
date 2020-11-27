#include <vulkan/vulkan.hpp>

#include <iostream>
#include <vector>

#include <vkImageIntegrationLib.h>

using namespace std;


bool check_queue_support(vk::QueueFamilyProperties q_fam) {
	bool supports_compute = false;
	bool supports_transfer = false;

	supports_compute = bool(vk::QueueFlagBits::eCompute & q_fam.queueFlags) || supports_compute;
	supports_transfer = bool(vk::QueueFlagBits::eTransfer & q_fam.queueFlags) || supports_transfer;

	std::cout << "Queue number: " + to_string(q_fam.queueCount) << endl;
	std::cout << "Queue flags: " + to_string(q_fam.queueFlags) << endl;

	return supports_transfer && supports_compute;
}

vector<uint32_t> get_supported_queues(vk::PhysicalDevice pd) {
	
	std::cout << "Device: " + string(pd.getProperties().deviceName) << endl;
	vector<uint32_t> supported_queues;

	auto queues = pd.getQueueFamilyProperties();
	for (size_t i = 0; i < queues.size(); i++)
	{
		if (check_queue_support(queues[i]))
		{
			supported_queues.push_back(i);
		}
	}
	


	return supported_queues;
}

struct device_queues
{
	vk::PhysicalDevice pdev;
	vector<uint32_t> q_idxs;
};

std::vector<device_queues> get_supported_devices(vk::Instance instance) {
	std::vector<vk::PhysicalDevice> devices{ instance.enumeratePhysicalDevices() };
	std::vector<device_queues> supported_devices;

	for (vk::PhysicalDevice pd : devices) {
		auto supported_qs = get_supported_queues(pd);
		if (supported_qs.size() > 0){
			device_queues d;
			d.pdev = pd;
			d.q_idxs = supported_qs;
			supported_devices.push_back(d);
		}
	}

	return supported_devices;
}

int main()
{
    // Use validation layers if this is a debug build
    std::vector<const char*> layers;
#if defined(_DEBUG)
    layers.push_back("VK_LAYER_KHRONOS_validation");

#endif

    // VkApplicationInfo allows the programmer to specifiy some basic information about the
    // program, which can be useful for layers and tools to provide more debug information.
    vk::ApplicationInfo appInfo = vk::ApplicationInfo()
        .setPApplicationName("Test driver for vkImageIntegrationLib")
        .setApplicationVersion(1)
        .setPEngineName("vkImageIntegration")
        .setEngineVersion(1)
        .setApiVersion(VK_API_VERSION_1_0);



	vkII::vkImageIntegration integrator = vkII::vkImageIntegration();

	vkII::Image img1(10000, 10000);

	integrator.do_comp();


    return 0;
}


