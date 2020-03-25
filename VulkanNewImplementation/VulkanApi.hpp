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
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Api Implementation", nullptr, nullptr);
	}

	void initVulkan() 
	{
		createInstance();
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
		vkDestroyInstance(instance, nullptr);

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	// ===== Member fields ==================
	GLFWwindow* window;
	VkInstance instance;

	// ===== Member function prototypes =====
	// VulkanApiInstance.cpp
		void createInstance();
		bool checkRequiredExtensionsAvailability(const char** requiredExtensions, uint32_t requiredExtensionsCount);
	// VulkanApiValidationLayers.cpp
		bool checkValidationLayerSupport();
};

#endif // !VULKAN_API

