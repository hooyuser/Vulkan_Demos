#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 aLocalPos;

void main() {
    gl_Position =  vec4(aLocalPos, 1.0);
}