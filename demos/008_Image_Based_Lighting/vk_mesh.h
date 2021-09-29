#pragma once

#include "vk_types.h"
#include "vk_buffer.h"
#include <glm/vec3.hpp>
#include <vector>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

    static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();

    static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

    bool operator==(const Vertex& other) const {
        return pos == other.pos && color == other.color && texCoord == other.texCoord;
    }
};

class Mesh;
using MeshPtr = std::shared_ptr<Mesh>;
class Mesh {
public:
    std::vector<Vertex> _vertices;
    std::vector<uint32_t> _indices;
    BufferPtr pVertexBuffer;
    BufferPtr pIndexBuffer;
    static MeshPtr createFromObj(const char* filename);
    static MeshPtr createFromObj(VulkanEngine* engine, const char* filename);
};



