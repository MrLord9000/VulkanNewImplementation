#ifndef VULKAN_API
#define VULKAN_API

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <optional>

#include "VulkanApiHelpers.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;

// ===== Validation layers list =========================================
const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

// ===== Simple way of handling if validation layers should be used =====
#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

// ===== Queue faliy indices structure =====
struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;

	bool isComplete()
	{
		return graphicsFamily.has_value();
	}
};

class VulkanApi 
{
public:
	void run() 
	{
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

private:
	void initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Api Implementation", nullptr, nullptr);
	}

	void initVulkan() 
	{
		createInstance();
		setupDebugMessenger();
		pickPhysicalDevice();
		createLogicalDevice();
	}

	void mainLoop() 
	{
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}
	}

	void cleanup() 
	{
		vkDestroyDevice(device, nullptr);

		if (enableValidationLayers)
		{
			// Destroy messenger function from VulkanApiHelpers.hpp
			DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
		}

		vkDestroyInstance(instance, nullptr);

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	// ===== Member fields ==================
	GLFWwindow* window;
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE; // No need to destroy it in the cleanup
	VkDevice device;
	VkQueue graphicsQueue; // Destroyed by device

	// ===== Member function prototypes =====
	// VulkanApiInstance.cpp
		void createInstance();
		bool checkRequiredExtensionsAvailability(const char** requiredExtensions, uint32_t requiredExtensionsCount);
		std::vector<const char*> getRequiredExtensions();
	// VulkanApiValidationLayers.cpp
		bool checkValidationLayerSupport();
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData); 
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void setupDebugMessenger();
	// VulkanApiPhysicalDevice.cpp
		void pickPhysicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	// VulkanApiLogicalDevice.cpp
		void createLogicalDevice();
};

#endif // !VULKAN_API

