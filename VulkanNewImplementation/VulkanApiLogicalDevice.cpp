#include "VulkanApi.hpp"

void VulkanApi::createLogicalDevice()
{
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

	VkDeviceQueueCreateInfo queueCreateInfo = {};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
	queueCreateInfo.queueCount = 1;

	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;
	queueCreateInfo.pNext = nullptr;

	// We'll come back here to enable more interesting functions of Vulkan
	VkPhysicalDeviceFeatures deviceFeatures = {};

	// ===== Creating the logical device =====
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;
	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = 0; // For now
	createInfo.pNext = nullptr;

	// Turns out setting validation layers here doesn't work anymore
	//if (enableValidationLayers)
	//{
	//	// For backwards compatibility sake
	//	createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
	//	createInfo.ppEnabledExtensionNames = validationLayers.data();
	//}
	//else
	//{
	//	createInfo.enabledLayerCount = 0;
	//}
	createInfo.enabledLayerCount = 0;

	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create logical device!");
	}

	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
}