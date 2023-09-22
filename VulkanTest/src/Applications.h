#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

class HelloTriangleApplication {
	public:
		void run();
	private:
		void initWindow();
		void initVulkan();
		std::vector<const char*> getRequiredExtensions();
		void createInstance();
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void setupDebugMessenger();
		void pickPhysicalDevice();
		int rateDeviceSuitability(VkPhysicalDevice device);
		bool checkValidationLayerSupport();
		void mainLoop();
		void cleanup();

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);

		GLFWwindow* window;
		const uint32_t WINDOW_WIDTH = 800;
		const uint32_t WINDOW_HEIGHT = 600;

		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

		const std::vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};

		#ifdef NDEBUG
		const bool enableValidationLayers = false;
		#else
		const bool enableValidationLayers = true;
		#endif
};