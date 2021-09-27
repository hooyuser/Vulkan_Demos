#pragma once
#include "vk_types.h"

class VulkanEngine;

namespace vk_base {
	class Buffer {
	public:
		VkDevice device;

		VkBuffer buffer;
		VkDeviceMemory memory;

		Buffer() :device(VK_NULL_HANDLE), buffer(VK_NULL_HANDLE), memory(VK_NULL_HANDLE) {}
			
		Buffer(VkDevice device, VkPhysicalDevice physicalDevice, VkBufferUsageFlags bufferUsage, VkMemoryPropertyFlags memoryProperties, VkDeviceSize size);

		~Buffer();
	};
}

namespace engine {
	class Buffer : public vk_base::Buffer {
		using Base = vk_base::Buffer;
		using Base::Base;
		using BufferPtr = std::shared_ptr<Buffer>;
	public:
		static BufferPtr createBuffer(VulkanEngine& engine, VkBufferUsageFlags bufferUsage, VkMemoryPropertyFlags memoryProperties, VkDeviceSize size, CreateResourceFlagBits bufferDescription);
	};
}

