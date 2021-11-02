#version 450

#define PI 3.14159265359

layout (constant_id = 0) const int textureCubemapArraySize = 1;                                               
layout (constant_id = 1) const int irradianceMapId = 0;  
layout (constant_id = 2) const int brdfLUTId = 0;        
layout (constant_id = 3) const int prefilteredMap20Id = 0; 
layout (constant_id = 4) const int prefilteredMap40Id = 0; 
layout (constant_id = 5) const int prefilteredMap60Id = 0;
layout (constant_id = 6) const int prefilteredMap80Id = 0;
layout (constant_id = 7) const int prefilteredMap100Id = 0;

layout (constant_id = 8) const int texture2DArraySize = 1;
layout (constant_id = 9) const int baseColorTextureId = -1;
layout (constant_id = 10) const float baseColorRed = 1.0;   
layout (constant_id = 11) const float baseColorGreen = 0.0;  
layout (constant_id = 12) const float baseColorBlue = 1.0;  


layout(set = 0, binding = 1) uniform sampler2D textureArray[texture2DArraySize];
layout(set = 0, binding = 2) uniform samplerCube cubemapArray[textureCubemapArraySize];

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 normal;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 baseColor;
    if(baseColorTextureId >= 0) {
        baseColor = texture(textureArray[baseColorTextureId], fragTexCoord).xyz;
    } else {
        baseColor = vec3(baseColorRed, baseColorGreen, baseColorBlue);
    }
    vec3 F = vec3(1.0);
    vec3 diffuse = baseColor * (1.0 - 0.0) * F * texture(cubemapArray[irradianceMapId], normal).xyz / PI;
    outColor = vec4(diffuse, 1.0);
}