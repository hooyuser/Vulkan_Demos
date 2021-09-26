#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 fragPos;
layout(location = 0) out vec4 outColor;

#define PI 3.14159265359

uvec2 Sobol(uint n) {
    uvec2 p = uvec2(0u);
    uvec2 d = uvec2(0x80000000u);

    for (; n != 0u; n >>= 1u) {
        if ((n & 1u) != 0u) {
            p ^= d;
        }
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

vec2 sobol2d(uint index) {
    uvec2 p = Sobol(index);
    p.x = OwenScramble(p.x, 0xe7843fbfu);
    p.y = OwenScramble(p.y, 0x8d8fb1e0u);
    return vec2(p) / float(0xffffffffu);
}

vec2 sobol2d(uint index, uint seed) {
    uvec2 p = Sobol(index);
    uint seed1 = OwenHash(0xe7843fbfu, seed);
    p.x = OwenScramble(p.x, seed1);
    p.y = OwenScramble(p.y, OwenHash(0x8d8fb1e0u, seed1));
    return vec2(p) / float(0xffffffffu);
}

vec3 genHalfVector(uint index, uint seed, float alpha) {
    vec2 psi = sobol2d(index, seed);
    float a_sqr = alpha * alpha;
    float denominator = 1.0 - (1.0 - a_sqr) * psi.x;
    float part = alpha * sqrt(psi.x / denominator);
    float Nu_z = part * cos(2.0 * PI * psi.y);
    float Nu_x = part * sin(2.0 * PI * psi.y);
    float Nu_y = sqrt((1.0 - psi.x) / denominator);
    return vec3(Nu_x, Nu_y, Nu_z);
}


vec2 IntegrateBRDF(float NdotWo, float roughness) {
    float a = roughness * roughness;
    vec3 Wo;
    Wo.z = sqrt(1.0 - NdotWo * NdotWo);
    Wo.x = 0.0;
    Wo.y = NdotWo;

    float A = 0.0;
    float B = 0.0;
    vec3 N = vec3(0.0, 1.0, 0.0);

    const uint SAMPLE_COUNT = 65536u;
    for (uint k = 0u; k < SAMPLE_COUNT; ++k) {
        uint seed = OwenHash(uint(gl_FragCoord.x), uint(gl_FragCoord.y));
        vec3 H = genHalfVector(k, seed, a);
        vec3 Wi  = normalize(2.0 * dot(Wo, H) * H - Wo);

        float NdotWi = max(Wi.y, 0.0);
        float NdotH = max(H.y, 0.0);
        float HdotWo = max(dot(Wo, H), 0.0);

        if (NdotWi > 0.0) {
            float G1 = NdotWi * (NdotWo * (1 - a) + a);
            float G2 = NdotWo * (NdotWi * (1 - a) + a);
            float G_Vis = 2 * (NdotWi * HdotWo) / (G1 + G2) / NdotH;
            float Fc = pow(1.0 - HdotWo, 5.0);
            A += (1.0 - Fc) * G_Vis;
            B += Fc * G_Vis;
        }
    }
    A /= float(SAMPLE_COUNT);
    B /= float(SAMPLE_COUNT);
    return vec2(A, B);
}


void main() {
    outColor = vec4(IntegrateBRDF(fragPos.x, fragPos.y), 0.0, 1.0);
}