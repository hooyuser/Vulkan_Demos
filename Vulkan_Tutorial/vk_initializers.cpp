#include <vk_initializers.h>
#include <vk_mesh.h>

VkCommandPoolCreateInfo vkinit::commandPoolCreateInfo(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flags /*= 0*/)
{
	VkCommandPoolCreateInfo commandPoolInfo = { VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };

	commandPoolInfo.pNext = nullptr;
	commandPoolInfo.queueFamilyIndex = queueFamilyIndex;
	commandPoolInfo.flags = flags;
	return commandPoolInfo;
}

VkCommandBufferAllocateInfo vkinit::commandBufferAllocateInfo(VkCommandPool pool, uint32_t count /*= 1*/, VkCommandBufferLevel level /*= VK_COMMAND_BUFFER_LEVEL_PRIMARY*/)
{
	VkCommandBufferAllocateInfo info = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };

	info.pNext = nullptr;
	info.commandPool = pool;
	info.commandBufferCount = count;
	info.level = level;
	return info;
}

VkPipelineShaderStageCreateInfo vkinit::pipelineShaderStageCreateInfo(VkShaderStageFlagBits stage, VkShaderModule shaderModule)
{
	VkPipelineShaderStageCreateInfo info{ VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO };

	info.pNext = nullptr;
	//shader stage
	info.stage = stage;
	//module containing the code for this shader stage
	info.module = shaderModule;
	//the entry point of the shader
	info.pName = "main";
	return info;
}

VkPipelineVertexInputStateCreateInfo vkinit::vertexInputStateCreateInfo(const std::vector<VkVertexInputBindingDescription>& bindingDescriptions, const std::vector<VkVertexInputAttributeDescription>& attributeDescriptions) {
	VkPipelineVertexInputStateCreateInfo vertexInputInfo = { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };

	vertexInputInfo.pNext = nullptr;

	//no vertex bindings or attributes
	vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescriptions.size());
	vertexInputInfo.pVertexBindingDescriptions = bindingDescriptions.data();

	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
	vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
	return vertexInputInfo;
}

VkPipelineInputAssemblyStateCreateInfo vkinit::inputAssemblyCreateInfo(VkPrimitiveTopology topology) {
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo = { VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };

	inputAssemblyInfo.pNext = nullptr;
	inputAssemblyInfo.topology = topology;
	//we are not going to use primitive restart on the entire tutorial so leave it on false
	inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;
	return inputAssemblyInfo;
}

VkPipelineViewportStateCreateInfo vkinit::viewportStateCreateInfo(const VkViewport& viewport, const VkRect2D& scissor) {
	VkPipelineViewportStateCreateInfo viewportState{ VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };

	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;
	return viewportState;
}

VkPipelineRasterizationStateCreateInfo vkinit::rasterizationStateCreateInfo(VkPolygonMode polygonMode)
{
	VkPipelineRasterizationStateCreateInfo rasterizerInfo = { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };

	rasterizerInfo.pNext = nullptr;
	rasterizerInfo.depthClampEnable = VK_FALSE;
	//rasterizer discard allows objects with holes, default to no
	rasterizerInfo.rasterizerDiscardEnable = VK_FALSE;

	rasterizerInfo.polygonMode = polygonMode;
	rasterizerInfo.lineWidth = 1.0f;
	rasterizerInfo.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizerInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	//no depth bias
	rasterizerInfo.depthBiasEnable = VK_FALSE;
	rasterizerInfo.depthBiasConstantFactor = 0.0f;
	rasterizerInfo.depthBiasClamp = 0.0f;
	rasterizerInfo.depthBiasSlopeFactor = 0.0f;

	return rasterizerInfo;
}

VkPipelineMultisampleStateCreateInfo vkinit::multisamplingStateCreateInfo(VkSampleCountFlagBits msaaSamples)
{
	VkPipelineMultisampleStateCreateInfo multisamplingInfo = { VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };

	multisamplingInfo.pNext = nullptr;
	multisamplingInfo.sampleShadingEnable = VK_FALSE;
	//multisampling defaulted to no multisampling (1 sample per pixel)
	multisamplingInfo.rasterizationSamples = msaaSamples;
	// multisamplingInfo.minSampleShading = 1.0f;
	multisamplingInfo.pSampleMask = nullptr;
	multisamplingInfo.alphaToCoverageEnable = VK_FALSE;
	multisamplingInfo.alphaToOneEnable = VK_FALSE;
	return multisamplingInfo;
}

VkPipelineDepthStencilStateCreateInfo vkinit::depthStencilCreateInfo(VkCompareOp compareOp) {
	VkPipelineDepthStencilStateCreateInfo depthStencilInfo{ VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };
	
	depthStencilInfo.depthTestEnable = VK_TRUE;
	depthStencilInfo.depthWriteEnable = VK_TRUE;
	depthStencilInfo.depthCompareOp = compareOp;
	depthStencilInfo.depthBoundsTestEnable = VK_FALSE;
	depthStencilInfo.stencilTestEnable = VK_FALSE;
	return depthStencilInfo;
}

VkPipelineColorBlendAttachmentState vkinit::colorBlendAttachmentState() {
	VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
	
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
		VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;
	return colorBlendAttachment;
}

VkPipelineColorBlendStateCreateInfo vkinit::colorBlendAttachmentCreateInfo(VkPipelineColorBlendAttachmentState& colorBlendAttachment) {
	VkPipelineColorBlendStateCreateInfo colorBlending{ VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };
	
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;
	return colorBlending;
}

VkPipelineLayoutCreateInfo vkinit::pipelineLayoutCreateInfo(const VkDescriptorSetLayout& descriptorSetLayout) {
	VkPipelineLayoutCreateInfo pipelineLayoutInfo{ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };

	pipelineLayoutInfo.pNext = nullptr;
	//empty defaults
	pipelineLayoutInfo.flags = 0;

	pipelineLayoutInfo.setLayoutCount = 1;
	pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;

	pipelineLayoutInfo.pushConstantRangeCount = 0;
	pipelineLayoutInfo.pPushConstantRanges = nullptr;
	return pipelineLayoutInfo;
}