#version 450

layout (constant_id = 0) const bool useBaseColorTexture = false;
layout (constant_id = 1) const float baseColorRed = 1.0;
layout (constant_id = 2) const float baseColorGreen = 0.0;
layout (constant_id = 3) const float baseColorBlue = 1.0;

layout(set = 1, binding = 0) uniform sampler2D baseColorTexture;

layout(location = 0) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    if(useBaseColorTexture) {
        outColor = texture(baseColorTexture, fragTexCoord);
    } else {
        outColor = vec4(baseColorRed, baseColorGreen, baseColorBlue, 1.0);
    }
}