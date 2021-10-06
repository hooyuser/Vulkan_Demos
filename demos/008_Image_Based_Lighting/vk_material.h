#pragma once
#include "vk_types.h"
#include "Reflect.h"
#include <string>

using namespace Reflect;

struct PbrParameters {
	VkBool32 useBaseColorTexture = false;
	float baseColorRed = 1.0;
	float baseColorGreen = 1.0;
	float baseColorBlue = 1.0;

	REFLECT(PbrParameters, useBaseColorTexture, baseColorRed, baseColorGreen, baseColorBlue)
};

namespace engine {
	class Shader;

	struct TextureSet {
		std::string textureName = "";
		VkDescriptorSet descriptorSet = VK_NULL_HANDLE;
		TextureSet() {}
		TextureSet(std::string textureName, VkDescriptorSet descriptorSet = VK_NULL_HANDLE):textureName(textureName), descriptorSet(descriptorSet){}
		TextureSet(const TextureSet& textureSet) : textureName(textureSet.textureName), descriptorSet(textureSet.descriptorSet) {}
		TextureSet(TextureSet&& textureSet): textureName(textureSet.textureName), descriptorSet(textureSet.descriptorSet){}
		//TextureSet(std::string&& textureName, VkDescriptorSet&& descriptorSet) :textureName(textureName), descriptorSet(descriptorSet) {}
	};

	using ShaderPtr = std::shared_ptr<Shader>;
	struct Material {
		
		ShaderPtr pShaders;
		PbrParameters paras;
		TextureSetFlagBits textureSetFlagBits = None;
		VkPipeline pipeline = VK_NULL_HANDLE;
		VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
		std::unordered_map<std::string, TextureSet> textureSets;
		//VkDescriptorSet textureSet = VK_NULL_HANDLE;
		inline Material() {}
		inline Material(VkPipeline pipeline, VkPipelineLayout pipelineLayout) :pipeline(pipeline), pipelineLayout(pipelineLayout) {
		}
	};
}

using MaterialPtr = std::shared_ptr<engine::Material>;

