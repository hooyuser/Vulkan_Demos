#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 aLocalPos;
layout(location = 0) out vec2 fragPos;

void main() {
    fragPos = aLocalPos.xy * 0.5 + 0.5;
    gl_Position =  vec4(aLocalPos, 1.0);
}