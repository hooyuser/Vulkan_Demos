#pragma once
#include "vk_types.h"
#include "Reflect.h"
#include <variant>
#include <string>

using namespace Reflect;

struct Pbr {
	int textureCubemapArraySize = 1;
	int irradianceMapId = 0;
	int brdfLUTId = 0;
	int prefilteredMap20Id = 0;
	int prefilteredMap40Id = 0;
	int prefilteredMap60Id = 0;
	int prefilteredMap80Id = 0;
	int prefilteredMap100Id = 0;

	int texture2DArraySize = 1;
	int baseColorTextureID = -1;
	float baseColorRed = 1.0;
	float baseColorGreen = 0.0;
	float baseColorBlue = 1.0;

	REFLECT(Pbr,
		textureCubemapArraySize,
		irradianceMapId,
		brdfLUTId,
		prefilteredMap20Id,
		prefilteredMap40Id,
		prefilteredMap60Id,
		prefilteredMap80Id,
		prefilteredMap100Id,
		texture2DArraySize,
		baseColorTextureID,
		baseColorRed,
		baseColorGreen,
		baseColorBlue)
};

struct HDRi {

	int textureCubemapArraySize = 0;
	int baseColorTextureID = -1;
	
	REFLECT(HDRi,
		textureCubemapArraySize, 
		baseColorTextureID)
};



namespace engine {
	class Shader;

	//struct TextureSet {
		//int textureID = -1;
		//VkDescriptorSet descriptorSet = VK_NULL_HANDLE;
		//TextureSet() {}
		//TextureSet(int textureID, VkDescriptorSet descriptorSet = VK_NULL_HANDLE):textureID(textureID), descriptorSet(descriptorSet){}
		//TextureSet(const TextureSet& textureSet) : textureID(textureSet.textureID), descriptorSet(textureSet.descriptorSet) {}
		//TextureSet(TextureSet&& textureSet): textureID(textureSet.textureID), descriptorSet(textureSet.descriptorSet){}
		//TextureSet(std::string&& textureName, VkDescriptorSet&& descriptorSet) :textureName(textureName), descriptorSet(descriptorSet) {}
	//};

	using ShaderPtr = std::shared_ptr<Shader>;

	

	template <typename ParaT>
	class Material {
	public:
		ShaderPtr pShaders;
		ParaT paras;
		//ShaderFlagBits shaderFlagBits = PBR;
		VkPipeline pipeline = VK_NULL_HANDLE;
		VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
		std::unordered_map<std::string, int> textureArrayIndex;
		//VkDescriptorSet textureSet = VK_NULL_HANDLE;


		//inline Material() {}
		//inline Material(VkPipeline pipeline, VkPipelineLayout pipelineLayout) :pipeline(pipeline), pipelineLayout(pipelineLayout) {
		//}
	};

	
	using PbrMaterial = Material<Pbr>;
	using HDRiMaterial = Material<HDRi>;
	using PbrMaterialPtr = std::shared_ptr<PbrMaterial>;
	using HDRiMaterialPtr = std::shared_ptr<HDRiMaterial>;

	using MaterialV = std::variant<PbrMaterial, HDRiMaterial>;
	using MaterialPtrV = std::variant<PbrMaterialPtr, HDRiMaterialPtr>;
}



