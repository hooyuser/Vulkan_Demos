#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform sampler2D equirectangularMap;

layout(location = 0) in vec3 localPos;
layout(location = 0) out vec4 outColor;

const vec2 invAtan = vec2(0.1591, 0.3183);

vec2 SampleSphericalMap(vec3 v) {
    vec2 uv = vec2(atan(v.x, v.z), acos(v.y));
    uv *= invAtan;
    uv.x = 0.5 - uv.x;
    return uv;
}

void main() {
    vec2 uv = SampleSphericalMap(normalize(localPos)); 
    vec3 color = texture(equirectangularMap, uv).rgb;
    outColor = vec4(color, 1.0);
}