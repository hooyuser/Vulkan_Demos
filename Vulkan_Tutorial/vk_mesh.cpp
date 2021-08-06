#include <vk_mesh.h>
#include <util.h>

#include <array>

std::vector<VkVertexInputBindingDescription> Vertex::getBindingDescriptions() {
	std::vector<VkVertexInputBindingDescription> bindingDescriptions{};

	VkVertexInputBindingDescription bindingDescription{};
	bindingDescription.binding = 0;
	bindingDescription.stride = sizeof(Vertex);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	bindingDescriptions.push_back(bindingDescription);
	return bindingDescriptions;
}

std::vector<VkVertexInputAttributeDescription> Vertex::getAttributeDescriptions() {
	std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};
	attributeDescriptions.reserve(CountMember<Vertex>::value);

	//Position will be stored at Location 0
	VkVertexInputAttributeDescription posAttributeDescription = {};
	posAttributeDescription.binding = 0;
	posAttributeDescription.location = 0;
	posAttributeDescription.format = VK_FORMAT_R32G32B32_SFLOAT;
	posAttributeDescription.offset = offsetof(Vertex, pos);

	//Normal will be stored at Location 1
	VkVertexInputAttributeDescription colorAttributeDescription = {};
	colorAttributeDescription.binding = 0;
	colorAttributeDescription.location = 1;
	colorAttributeDescription.format = VK_FORMAT_R32G32B32_SFLOAT;
	colorAttributeDescription.offset = offsetof(Vertex, color);

	//Position will be stored at Location 2
	VkVertexInputAttributeDescription texCoordAttributeDescription = {};
	texCoordAttributeDescription.binding = 0;
	texCoordAttributeDescription.location = 2;
	texCoordAttributeDescription.format = VK_FORMAT_R32G32B32_SFLOAT;
	texCoordAttributeDescription.offset = offsetof(Vertex, texCoord);

	attributeDescriptions.push_back(posAttributeDescription);
	attributeDescriptions.push_back(colorAttributeDescription);
	attributeDescriptions.push_back(texCoordAttributeDescription);

	return attributeDescriptions;
}
