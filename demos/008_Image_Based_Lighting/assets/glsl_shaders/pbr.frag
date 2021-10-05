#version 450

layout (constant_id = 0) const bool useBaseColorTexture = true;
layout (constant_id = 1) const float baseColorRed = 1.0;
layout (constant_id = 2) const float baseColorGreen = 1.0;
layout (constant_id = 3) const float baseColorBlue = 1.0;

layout(set = 1, binding = 0) uniform sampler2D baseColorTexture;

layout(location = 0) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = texture(baseColorTexture, fragTexCoord);
}