#pragma once

#include "vk_types.h"
#include "vk_engine.h"

struct Image: AllocatedImage {
	VkImageView _imageView;
};

struct Texture: Image {
	VkSampler _imageSampler;

	void createCubemapTexture();

};
