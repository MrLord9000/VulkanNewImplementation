#include "VulkanApi.hpp"

void VulkanApi::createInstance()
{
	// ===== Checking validation layers support =====
	if (enableValidationLayers && !checkValidationLayerSupport())
	{
		throw std::runtime_error("Validation layers requested, but not available!");
	}

	// ===== Application info struct =====
	// Note: Purely optional
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "VulkanApi implementation";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	appInfo.pEngineName = "Screensaver Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;
	// Note: pNext can point to extension information in the future

	// ===== Instance creation =====
	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	// Extensions from glfw
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	// TODO: Wrote by myself, can break
	if (!checkRequiredExtensionsAvailability(glfwExtensions, glfwExtensionCount))
	{
		throw std::runtime_error("You don't have the required extensions");
	}

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;
	
	createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create instance.");
	}
}

bool VulkanApi::checkRequiredExtensionsAvailability(const char** requiredExtensions, uint32_t requiredExtensionsCount)
{
	if (requiredExtensionsCount == 0)
	{
		return true;
	}

	// Enumerate available extensions
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	for (uint32_t i = 0; i < requiredExtensionsCount; ++i)
	{
		bool hasRequiredExtension = false;
		for (const auto& extension : extensions)
		{
			if (strcmp(extension.extensionName, requiredExtensions[i]) == 0)
			{
				hasRequiredExtension = true;
				break;
			}
		}

		if (!hasRequiredExtension)
		{
			return false;
		}
	}

	return true;
}