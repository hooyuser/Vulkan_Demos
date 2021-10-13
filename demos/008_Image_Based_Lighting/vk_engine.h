#pragma once

#include "vk_types.h"
#include "vk_mesh.h"
#include "vk_camera.h"
#include "vk_buffer.h"
#include "vk_image.h"
#include "vk_material.h"


// #define GLFW_INCLUDE_VULKAN

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <array>
#include <deque>

#include <set>
#include <span>
#include <unordered_map>


struct QueueFamilyIndices;
struct SwapChainSupportDetails;

struct FrameData {
	VkDescriptorSet sceneDescriptorSet;
};

struct DeletionQueue
{
	std::deque<std::function<void()>> deletors;

	void push_function(std::function<void()>&& function) {
		deletors.emplace_back(function);
	}

	void flush() {
		// reverse iterate the deletion queue to execute all the functions
		for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
			(*it)(); //call the function
		}

		deletors.clear();
	}
};

class PipelineBuilder {
public:
	std::vector<VkVertexInputBindingDescription> bindingDescriptions;
	std::vector<VkVertexInputAttributeDescription> attributeDescriptions;
	std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
	VkPipelineVertexInputStateCreateInfo vertexInput;
	VkPipelineInputAssemblyStateCreateInfo inputAssembly;
	VkViewport viewport;
	VkRect2D scissor;
	VkPipelineViewportStateCreateInfo viewportState;
	VkPipelineRasterizationStateCreateInfo rasterizer;
	VkPipelineColorBlendStateCreateInfo colorBlend;
	VkPipelineMultisampleStateCreateInfo multisampling;
	VkPipelineDepthStencilStateCreateInfo depthStencil;
	VkPipelineColorBlendAttachmentState colorBlendAttachment;
	std::vector<VkSpecializationMapEntry> specializationMapEntries;
	VkSpecializationInfo specializationInfo;

	PipelineBuilder(VulkanEngine* engine);

	void setShaderStages(MaterialPtr pMaterial);

	void buildPipeline(const VkDevice& device, const VkRenderPass& pass, const VkPipelineLayout& pipelineLayout, VkPipeline& pipeline);
};


struct RenderObject {
	MeshPtr mesh;
	MaterialPtr material;
	glm::mat4 transformMatrix;
};

class VulkanEngine {
public:
	bool isInitialized{ false };

	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}


	struct GLFWwindow* window{ nullptr };

	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkSurfaceKHR surface;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
	VkDevice device;

	VkQueue graphicsQueue;
	VkQueue presentQueue;
	QueueFamilyIndices queueFamilyIndices;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkRenderPass renderPass;
	VkDescriptorSetLayout sceneSetLayout;
	VkDescriptorSetLayout texSetLayout;
	VkPipelineLayout meshPipelineLayout;
	VkPipelineLayout envPipelineLayout;
	std::unordered_map<TextureSetFlagBits, VkPipeline> meshPipelines;
	VkPipeline envPipeline;

	VkCommandPool commandPool;

	ImagePtr pColorImage;
	ImagePtr pDepthImage;

	std::vector<RenderObject> renderables;

	std::unordered_map<std::string, MaterialPtr> materials;
	//MaterialPtr envMaterial;
	std::unordered_map<std::string, MeshPtr> meshes;
	std::vector<TexturePtr> loadedTexture2Ds;
	std::vector<TexturePtr> loadedTextureCubemaps;

	std::vector<BufferPtr> pUniformBuffers;

	VkDescriptorPool descriptorPool;

	std::vector<FrameData> frameData;

	std::vector<VkCommandBuffer> commandBuffers;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	std::vector<VkFence> imagesInFlight;
	size_t currentFrame = 0;

	bool framebufferResized = false;

	DeletionQueue mainDeletionQueue;
	DeletionQueue swapChainDeletionQueue;

	static Camera camera;
	static glm::vec2 mousePreviousPos;
	static glm::vec2 mouseDeltaPos;


	void initWindow();

	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	void initVulkan();

	void mainLoop();

	void cleanup();

	void recreateSwapChain();

	void createInstance();

	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	void setupDebugMessenger();

	void createSurface();

	void pickPhysicalDevice();

	void createLogicalDevice();

	void createSwapChain();

	void createImageViews();

	void parseMaterialInfo();

	void createRenderPass();

	void createDescriptorSetLayouts();

	void createGraphicsPipeline();

	void createMeshPipeline();

	void createEnvLightPipeline();

	void createFramebuffers();

	void createCommandPool();

	void createAttachments();

	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	VkFormat findDepthFormat();

	bool hasStencilComponent(VkFormat format);

	void createTextureImage();

	void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels, uint32_t layerCount = 1);

	VkSampleCountFlagBits getMaxUsableSampleCount();

	void createTextureImageView();

	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels, CreateResourceFlagBits imageViewDescription);

	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount = 1);

	void loadModel();

	void createUniformBuffers();

	void createDescriptorPool();

	void createDescriptorSets();

	void createTexDescriptorSet(TexturePtr loadedTexture, VkDescriptorSet& texDescriptorSet);

	VkCommandBuffer beginSingleTimeCommands();

	void endSingleTimeCommands(VkCommandBuffer commandBuffer);

	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	void createCommandBuffers();

	void createSyncObjects();

	void initScene();

	void updateUniformBuffer(uint32_t currentImage);

	void drawFrame();

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

	bool isDeviceSuitable(VkPhysicalDevice device);

	bool checkDeviceExtensionSupport(VkPhysicalDevice device);

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	std::vector<const char*> getRequiredExtensions();

	bool checkValidationLayerSupport();

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

	static void mouseCursorCallback(GLFWwindow* window, double xpos, double ypos);

	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	void setCamera();

	inline MaterialPtr createMaterial(VkPipeline pipeline, VkPipelineLayout layout, const std::string& name)
	{
		auto pMat = std::make_shared<engine::Material>(pipeline, layout);
		materials[name] = pMat;
		return materials[name];
	}

	void createDescriptorSetLayout(std::span<VkDescriptorSetLayoutBinding>&& descriptorSetLayoutBindings, VkDescriptorSetLayout& descriptorSetLayout);
};



