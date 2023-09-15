#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


class HelloTriangleApplication {
	public:
		void run();
	private:
		void initWindow();
		void initVulkan();
		void createInstance();
		void mainLoop();
		void cleanup();

		GLFWwindow* window;
		const uint32_t WINDOW_WIDTH = 800;
		const uint32_t WINDOW_HEIGHT = 600;

		VkInstance instance;
};