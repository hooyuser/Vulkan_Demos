#version 450

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

layout(location = 0) out vec4 outColor;

void main() {
    if(baseColorTextureId >= 0) {
        outColor = texture(textureArray[baseColorTextureId], fragTexCoord);
    } else {
        outColor = vec4(baseColorRed, baseColorGreen, baseColorBlue, 1.0);
    }
}