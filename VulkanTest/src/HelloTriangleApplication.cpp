#include "Applications.h"
#include <vector>
#include <iostream>

void HelloTriangleApplication::run() {
	initWindow();
	initVulkan();
	mainLoop();
	cleanup();
}

void HelloTriangleApplication::initWindow() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Vulkan", nullptr, nullptr);
}

void HelloTriangleApplication::initVulkan() {
	createInstance();
}

void HelloTriangleApplication::createInstance() {
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	uint32_t reqExtensionCount = 0;
	const char** requiredExtensions = glfwGetRequiredInstanceExtensions(&reqExtensionCount);

	// check all extensions are present 
	std::cout << "Validating Extensions:" << std::endl;
	bool allRequirementsPresent = true;
	for (int i = 0; i < reqExtensionCount; i++) {
		bool requirementFound = false;
		for (const auto& extension : extensions) {

			if (strcmp(extension.extensionName, requiredExtensions[i]) == 0) {
				requirementFound = true;
				std::cout << '\t' << requiredExtensions[i] << " Found!" << std::endl;
				break;
			}

		}

		if (!requirementFound) {
			allRequirementsPresent = false;
			std::cerr << '\t' << requiredExtensions[i] << " not Found!" << std::endl;
			break;
		}
	}

	if (allRequirementsPresent) {
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_3;


		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = 0;

		VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
	}
}

void HelloTriangleApplication::mainLoop() {
	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

	}
}

void HelloTriangleApplication::cleanup() {
	vkDestroyInstance(instance, nullptr);

	glfwDestroyWindow(window);

	glfwTerminate();
}
