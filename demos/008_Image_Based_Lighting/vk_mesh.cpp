#include "vk_mesh.h"
#include "util.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <stdexcept>

namespace std {
	template<> struct hash<Vertex> {
		size_t operator()(Vertex const& vertex) const {
			return hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
			//return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
		}
	};
}

std::vector<VkVertexInputBindingDescription> Vertex::getBindingDescriptions() {
	std::vector<VkVertexInputBindingDescription> bindingDescriptions{};

	VkVertexInputBindingDescription bindingDescription{};
	bindingDescription.binding = 0;
	bindingDescription.stride = sizeof(Vertex);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	bindingDescriptions.emplace_back(bindingDescription);
	return bindingDescriptions;
}

std::vector<VkVertexInputAttributeDescription> Vertex::getAttributeDescriptions() {
	std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};
	attributeDescriptions.reserve(CountMember<Vertex>::value);


	VkVertexInputAttributeDescription posAttributeDescription = {};
	posAttributeDescription.binding = 0;
	posAttributeDescription.location = 0;
	posAttributeDescription.format = VK_FORMAT_R32G32B32_SFLOAT;
	posAttributeDescription.offset = offsetof(Vertex, pos);


	VkVertexInputAttributeDescription texCoordAttributeDescription = {};
	texCoordAttributeDescription.binding = 0;
	texCoordAttributeDescription.location = 1;
	texCoordAttributeDescription.format = VK_FORMAT_R32G32B32_SFLOAT;
	texCoordAttributeDescription.offset = offsetof(Vertex, texCoord);

	attributeDescriptions.emplace_back(posAttributeDescription);
	attributeDescriptions.emplace_back(texCoordAttributeDescription);

	return attributeDescriptions;
}

MeshPtr Mesh::createFromObj(const char* filename) {
	auto mesh = std::make_shared<Mesh>();
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename)) {
		throw std::runtime_error(warn + err);
	}

	std::unordered_map<Vertex, uint32_t> uniqueVertices{};

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex vertex{};

			vertex.pos = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};

			vertex.texCoord = {
				attrib.texcoords[2 * index.texcoord_index + 0],
				1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
			};

			if (uniqueVertices.count(vertex) == 0) {
				uniqueVertices[vertex] = static_cast<uint32_t>(mesh->_vertices.size());
				mesh->_vertices.emplace_back(vertex);
			}

			mesh->_indices.emplace_back(uniqueVertices[vertex]);
		}
	}

	return mesh;
}

MeshPtr Mesh::loadFromObj(VulkanEngine* engine, const char* filename) {
	auto mesh = Mesh::createFromObj(filename);

	VkDeviceSize vertexbufferSize = sizeof(mesh->_vertices[0]) * mesh->_vertices.size();

	auto pStagingVertexBuffer = engine::Buffer::createBuffer(engine,
		vertexbufferSize,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		TEMP_BIT);

	pStagingVertexBuffer->copyFromHost(mesh->_vertices.data());

	mesh->pVertexBuffer = engine::Buffer::createBuffer(engine,
		vertexbufferSize,
		VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		BEFORE_SWAPCHAIN_BIT);

	mesh->pVertexBuffer->copyFromBuffer(engine, pStagingVertexBuffer->buffer);

	VkDeviceSize indexBufferSize = sizeof(mesh->_indices[0]) * mesh->_indices.size();

	auto pStagingIndexBuffer = engine::Buffer::createBuffer(engine,
		indexBufferSize,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		TEMP_BIT);

	pStagingIndexBuffer->copyFromHost(mesh->_indices.data());

	mesh->pIndexBuffer = engine::Buffer::createBuffer(engine,
		indexBufferSize,
		VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		BEFORE_SWAPCHAIN_BIT);

	mesh->pIndexBuffer->copyFromBuffer(engine, pStagingIndexBuffer->buffer);

	return mesh;
}
