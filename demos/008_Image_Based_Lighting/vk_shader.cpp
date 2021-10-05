#include "vk_shader.h"


#include <fstream>

//template <class R, class T>
//concept Matrix =
//std::convertible_to<
//	std::ranges::range_reference_t<std::ranges::range_reference_t<R>>,
//	T>;

namespace engine {
	using ShaderPtr = std::shared_ptr<Shader>;

	std::vector<char> readFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (!file.is_open()) {
			throw std::runtime_error("failed to open file!");
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
	}

	Shader::Shader(VkDevice device, std::vector<VkShaderModule>&& shaderModules): device(device), shaderModules(shaderModules){
	}

	Shader::~Shader() {
		for (auto& it : shaderModules) {
			vkDestroyShaderModule(device, it, nullptr);
		}
	}
}