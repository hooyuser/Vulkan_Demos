#version 450
#extension GL_KHR_vulkan_glsl: enable

layout(set = 0, binding = 2) uniform sampler2D texSampler;

layout(location = 0) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = texture(texSampler, fragTexCoord);
}