#include "vk_mesh.h"
#include "util.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <stdexcept>

namespace std {
	template<> struct hash<Vertex> {
		size_t operator()(Vertex const& vertex) const {
			return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
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

	attributeDescriptions.emplace_back(posAttributeDescription);
	attributeDescriptions.emplace_back(colorAttributeDescription);
	attributeDescriptions.emplace_back(texCoordAttributeDescription);

	return attributeDescriptions;
}

bool Mesh::loadFromObj(const char* filename) {
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

			vertex.color = { 1.0f, 1.0f, 1.0f };

			if (uniqueVertices.count(vertex) == 0) {
				uniqueVertices[vertex] = static_cast<uint32_t>(_vertices.size());
				_vertices.push_back(vertex);
			}

			_indices.push_back(uniqueVertices[vertex]);
		}
	}

	return true;
}
