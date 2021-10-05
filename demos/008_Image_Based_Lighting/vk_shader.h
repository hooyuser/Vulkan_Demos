#pragma once
#include "vk_types.h"
#include "vk_engine.h"
#include <iostream>
#include <string>


template <class R, class T>
concept Matrix =
std::convertible_to<
	std::ranges::range_reference_t<std::ranges::range_reference_t<R>>,
	T>;


namespace engine {
	std::vector<char> readFile(const std::string& filename);

	class Shader {
		using ShaderPtr = std::shared_ptr<Shader>;
	public:
		VkDevice device = VK_NULL_HANDLE;
		std::vector<VkShaderModule> shaderModules;

		Shader(VkDevice device, std::vector<VkShaderModule>&& shaderModules);

		~Shader();

		static ShaderPtr createFromSpv(VulkanEngine* engine, Matrix<char> auto const& spvFilePaths) {
			std::vector<VkShaderModule> shaderModuleVector;
			for (auto const& spvFilePath : spvFilePaths) {
				auto spvCode = readFile(spvFilePath);
				VkShaderModuleCreateInfo createInfo{};
				createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
				createInfo.codeSize = spvCode.size();
				createInfo.pCode = reinterpret_cast<const uint32_t*>(spvCode.data());

				VkShaderModule shaderModule;
				if (vkCreateShaderModule(engine->device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
					throw std::runtime_error("failed to create shader module!");
				}

				shaderModuleVector.emplace_back(std::move(shaderModule));
			}
			return std::make_shared<Shader>(engine->device, std::move(shaderModuleVector));
		}
	};
}

using ShaderPtr = std::shared_ptr<engine::Shader>;