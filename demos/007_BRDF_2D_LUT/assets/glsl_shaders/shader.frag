#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 outColor;

#define PI 3.14159265359
#define SAMPLE_NUM 524288
#define ALPHA 0.999999
#define F0 1

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

uint OwenHash(uint x, uint seed) { // works best with random seeds
    x ^= x * 0x3d20adeau;
    x += seed;
    x *= (seed >> 16) | 1u;
    x ^= x * 0x05526c56u;
    x ^= x * 0x53a22864u;
    return x;
}

uint OwenScramble(uint p, uint seed) {
    p = bitfieldReverse(p);
    p = OwenHash(p, seed);
    return bitfieldReverse(p);
}

vec2 sobol2d(uint index, uint seed) {
    uvec2 p = Sobol(index);
    p.x = OwenScramble(p.x, 0xe7843fbfu);
    p.y = OwenScramble(p.y, 0x8d8fb1e0u);
    return vec2(p) / float(0xffffffffu);
}

vec3 genNu(uint index, uint seed) {
    vec2 psi = sobol2d(index, seed);
    float a_sqr = ALPHA * ALPHA;
    float denominator = 1.0 - (1.0 - a_sqr) * psi.x;
    float numerator_part = 2.0 * ALPHA * sqrt(psi.x * (1.0 - psi.x));
    float Nu_z = numerator_part * cos(2.0 * PI * psi.y);
    float Nu_x = numerator_part * sin(2.0 * PI * psi.y);
    float Nu_y = 1.0 - (1.0 + a_sqr) * psi.x;
    return vec3(Nu_x, Nu_y, Nu_z) / denominator;
}

vec3 genSampleDirection(vec3 nu, vec3 N) {
    vec3 T = cross(vec3(0.0, 1.0, 0.0), N);
    vec3 B = cross(N, T);
    return B * nu.x + N * nu.y + T * nu.z;
}

void main() {
    outColor = vec4(1.0, 0.0, 0.1, 1.0);
}