#pragma once
#include "vk_types.h"
#include "Reflect.h"
#include <string>

using namespace Reflect;

struct PbrParameters {
	int texture2DArraySize = 0;
	int textureCubemapArraySize = 0;
	VkBool32 useBaseColorTexture = false;
	int baseColorTextureID = -1;
	float baseColorRed = 1.0;
	float baseColorGreen = 1.0;
	float baseColorBlue = 1.0;

	REFLECT(PbrParameters, texture2DArraySize, textureCubemapArraySize, useBaseColorTexture, baseColorTextureID, baseColorRed, baseColorGreen, baseColorBlue)
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
	class Material {
	public:
		ShaderPtr pShaders;
		PbrParameters paras;
		ShaderFlagBits shaderFlagBits = PBR;
		VkPipeline pipeline = VK_NULL_HANDLE;
		VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
		std::unordered_map<std::string, int> textureArrayIndex;
		//VkDescriptorSet textureSet = VK_NULL_HANDLE;
		inline Material() {}
		inline Material(VkPipeline pipeline, VkPipelineLayout pipelineLayout) :pipeline(pipeline), pipelineLayout(pipelineLayout) {
		}
	};
}

using MaterialPtr = std::shared_ptr<engine::Material>;

