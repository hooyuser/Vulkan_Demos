#version 450

layout (constant_id = 0) const int textureArraySize = 1;
layout (constant_id = 1) const int textureCubemapArraySize = 1;
layout (constant_id = 2) const bool useBaseColorTexture = false;
layout (constant_id = 3) const int baseColorTextureId = 0;
layout (constant_id = 4) const float baseColorRed = 1.0;
layout (constant_id = 5) const float baseColorGreen = 0.0;
layout (constant_id = 6) const float baseColorBlue = 1.0;

layout(set = 0, binding = 1) uniform sampler2D textureArray[textureArraySize];


layout(location = 0) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    if(useBaseColorTexture) {
        outColor = texture(textureArray[baseColorTextureId], fragTexCoord);
    } else {
        outColor = vec4(baseColorRed, baseColorGreen, baseColorBlue, 1.0);
    }
}