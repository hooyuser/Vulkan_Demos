#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform samplerCube cubeMap;

layout(location = 0) in vec3 localPos;
layout(location = 0) out vec4 outColor;

#define PI 3.14159265359
#define SAMPLE_NUM 512

uvec2 Sobol(uint n) {
    uvec2 p = uvec2(0u);
    uvec2 d = uvec2(0x80000000u);

    for(; n != 0u; n >>= 1u) {
        if((n & 1u) != 0u)
            p ^= d;
        
        d.x >>= 1u; // 1st dimension Sobol matrix, is same as base 2 Van der Corput
        d.y ^= d.y >> 1u; // 2nd dimension Sobol matrix
    }
    
    return p;
}

// adapted from: https://www.shadertoy.com/view/3lcczS
uint ReverseBits(uint x) {
    x = ((x & 0xaaaaaaaau) >> 1) | ((x & 0x55555555u) << 1);
    x = ((x & 0xccccccccu) >> 2) | ((x & 0x33333333u) << 2);
    x = ((x & 0xf0f0f0f0u) >> 4) | ((x & 0x0f0f0f0fu) << 4);
    x = ((x & 0xff00ff00u) >> 8) | ((x & 0x00ff00ffu) << 8);
    return (x >> 16) | (x << 16);
}

// EDIT: updated with a new hash that fixes an issue with the old one.
// details in the post linked at the top.
uint OwenHash(uint x, uint seed) { // works best with random seeds
    x ^= x * 0x3d20adeau;
    x += seed;
    x *= (seed >> 16) | 1u;
    x ^= x * 0x05526c56u;
    x ^= x * 0x53a22864u;
    return x;
}

uint OwenScramble(uint p, uint seed) {
    p = ReverseBits(p);
    p = OwenHash(p, seed);
    return ReverseBits(p);
}

vec2 sobol2d(uint index, uint seed) {
    uvec2 p = Sobol(index);
    p.x = OwenScramble(p.x, 0xe7843fbfu);
    p.y = OwenScramble(p.y, 0x8d8fb1e0u);
    return vec2(p) / float(0xffffffffu);
}

vec3 genNu(uint index, uint seed) {
    vec2 psi = sobol2d(index, seed);
    float a = sqrt(psi.x);
    float b = 2.0 * PI * psi.y;
    return vec3(a * cos(b), a * sin(b), sqrt(1.0 -psi.x));
}

vec3 genSampleDirection(vec3 nu, vec3 N) {
    vec3 T = cross(vec3(0.0,0.0,1.0), N);
    vec3 B = cross(N, T);
    return vec3(T.x*nu.x + B.x*nu.y + N.x*nu.z, T.y*nu.x + B.y*nu.y + N.y*nu.z, T.z*nu.x + B.z*nu.y + N.z*nu.z);
}

void main() {
    vec3 irradiance = vec3(0.0);
    for(int i =0; i < SAMPLE_NUM; i++){
        uint seed = uint(float(0x00004000u) * gl_FragCoord.x + float(0x40000000u) * gl_FragCoord.y);
        vec3 nu = genNu(i, seed);
        vec3 dir = genSampleDirection(nu, normalize(localPos));
        irradiance += texture(cubeMap, dir).rgb;
    }
    irradiance /= float(SAMPLE_NUM);
    outColor = vec4(irradiance, 1.0);
}