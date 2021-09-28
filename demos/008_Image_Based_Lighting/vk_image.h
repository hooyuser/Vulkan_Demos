#pragma once
#include "vk_types.h"

class VulkanEngine;


namespace vk_base {
	class Image {
	public:
		VkDevice device = VK_NULL_HANDLE;

		VkImage image = VK_NULL_HANDLE;
		VkDeviceMemory memory = VK_NULL_HANDLE;
		VkImageView imageView = VK_NULL_HANDLE;

		Image(VkDevice device, VkPhysicalDevice physicalDevice, uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImageAspectFlags aspectFlags);

		~Image();
	};


//struct Texture: Image {
//	VkSampler sampler;
//
//	void createCubemapTexture();
//
//};
}



namespace engine {
	class Image : public vk_base::Image {
		using Base = vk_base::Image;
		using Base::Base;
		using ImagePtr = std::shared_ptr<Image>;
	public:
		static ImagePtr createImage(VulkanEngine& engine, uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImageAspectFlags aspectFlags, CreateResourceFlagBits imageDescription);
	};
}
using ImagePtr = std::shared_ptr<engine::Image>;



