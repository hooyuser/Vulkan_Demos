#pragma once
#include <vulkan/vulkan.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#include <optional>

typedef enum CreateResourceFlagBits {
    TEMP_BIT = 0x00000000,
    BEFORE_SWAPCHAIN_BIT = 0x00000001,
    AFTER_SWAPCHAIN_BIT = 0x00000003,
} CreateResourceFlagBits;


struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

struct AllocatedBuffer {
    VkBuffer _buffer;
    VkDeviceMemory _bufferMemory;
};


