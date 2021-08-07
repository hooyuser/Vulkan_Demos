#pragma once

#include <vk_types.h>
#include <vector>

namespace vkinit {
	VkCommandPoolCreateInfo commandPoolCreateInfo(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flags = 0);

	VkRenderPassBeginInfo renderPassBeginInfo(VkRenderPass renderPass, VkExtent2D windowExtent, VkFramebuffer framebuffer);

	VkCommandBufferAllocateInfo commandBufferAllocateInfo(VkCommandPool pool, uint32_t count = 1, VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);

	VkPipelineShaderStageCreateInfo pipelineShaderStageCreateInfo(VkShaderStageFlagBits stage, VkShaderModule shaderModule);

	VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo(const std::vector<VkVertexInputBindingDescription>& bindingDescriptions, const std::vector<VkVertexInputAttributeDescription>& attributeDescriptions);

	VkPipelineInputAssemblyStateCreateInfo inputAssemblyCreateInfo(VkPrimitiveTopology topology);

	VkPipelineViewportStateCreateInfo viewportStateCreateInfo(const VkViewport& viewport, const VkRect2D& scissor);

	VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo(VkPolygonMode polygonMode);

	VkPipelineMultisampleStateCreateInfo multisamplingStateCreateInfo(VkSampleCountFlagBits msaaSamples);

	VkPipelineDepthStencilStateCreateInfo depthStencilCreateInfo(VkCompareOp compareOp);

	VkPipelineColorBlendAttachmentState colorBlendAttachmentState();

	VkPipelineColorBlendStateCreateInfo colorBlendAttachmentCreateInfo(VkPipelineColorBlendAttachmentState& colorBlendAttachment);

	VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo(const VkDescriptorSetLayout& descriptorSetLayout);
}