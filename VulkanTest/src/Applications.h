#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstdint>
#include <vector>
#include <optional>


struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

const int MAX_FRAMES_IN_FLIGHT = 2;

class HelloTriangleApplication {
	public:
		void run();
	private:
		void initWindow();
		void initVulkan();
		void mainLoop();
		void cleanup();
		
		bool checkValidationLayerSupport();
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);

		std::vector<const char*> getRequiredExtensions();
		void createInstance();
		
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void setupDebugMessenger();
		
		void pickPhysicalDevice();
		int rateDeviceSuitability(VkPhysicalDevice device);
		void createLogicalDevice();
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		void createSurface();
		
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		void createSwapChain();
		void recreateSwapChain();
		void cleanupSwapChain();
		void createImageViews();
		void createRenderPass();
		void createGraphicsPipeline();
		void createFrameBuffers();
		void createCommandPool();
		void createCommandBuffers();
		void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
		void createSyncObjects();


		void drawFrame();

		VkShaderModule createShaderModule(const std::vector<char>& code);

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);
		static void frameBufferResizeCallback(GLFWwindow* window, int width, int height);

		GLFWwindow* window;
		const uint32_t WINDOW_WIDTH = 800;
		const uint32_t WINDOW_HEIGHT = 600;
		uint32_t currentFrame = 0;

		VkSurfaceKHR surface;
		VkQueue presentQueue;
		VkRenderPass renderPass;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;

		VkSwapchainKHR swapChain;
		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		std::vector<VkImageView> swapChainImageViews;
		std::vector<VkFramebuffer> swapChainFrameBuffers;

		VkCommandPool commandPool;
		std::vector<VkCommandBuffer> commandBuffers;
		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;

		bool frameBufferResized = false;

		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device;
		VkQueue graphicsQueue;

		const std::vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};

		const std::vector<const char*> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		#ifdef NDEBUG
		const bool enableValidationLayers = false;
		#else
		const bool enableValidationLayers = true;
		#endif
};