#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    int index;
} ubo;

layout(push_constant) uniform PushConstant {
    int index;
} constant;

layout(location = 0) in vec3 aLocalPos;

layout(location = 0) out vec3 localPos;


const mat4 mProjViews[6] = {
    {{0.000000, 0.000000, -1.010101, -1.000000}, {0.000000, 1.000000, 0.000000, 0.000000}, {-1.000000, 0.000000, 0.000000, 0.000000}, {0.000000, 0.000000, 1.919192, 2.000000}},
    {{0.000000, 0.000000, 1.010101, 1.000000}, {0.000000, 1.000000, 0.000000, 0.000000}, {1.000000, 0.000000, 0.000000, 0.000000}, {0.000000, 0.000000, 1.919192, 2.000000}},
    {{1.000000, 0.000000, 0.000000, 0.000000}, {0.000000, 0.000000, -1.010101, -1.000000}, {0.000000, -1.000000, 0.000000, 0.000000}, {0.000000, 0.000000, 1.919192, 2.000000}},
    {{1.000000, 0.000000, 0.000000, 0.000000}, {0.000000, 0.000000, 1.010101, 1.000000}, {0.000000, 1.000000, 0.000000, 0.000000}, {0.000000, 0.000000, 1.919192, 2.000000}},
    {{1.000000, 0.000000, 0.000000, 0.000000}, {0.000000, 1.000000, 0.000000, 0.000000}, {0.000000, 0.000000, -1.010101, -1.000000}, {0.000000, 0.000000, 1.919192, 2.000000}},
    {{-1.000000, 0.000000, 0.000000, 0.000000}, {0.000000, 1.000000, 0.000000, 0.000000}, {0.000000, 0.000000, 1.010101, 1.000000}, {0.000000, 0.000000, 1.919192, 2.000000}}
};

void main() {
    localPos = aLocalPos;
    gl_Position = mProjViews[constant.index] * vec4(aLocalPos, 1.0);
}