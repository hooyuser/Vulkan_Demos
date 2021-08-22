#include <string>
#include <vector>
#include <iostream>

#include"file_io.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif
#define TINYEXR_USE_THREAD 1
#define TINYEXR_USE_OPENMP 1
#define TINYEXR_IMPLEMENTATION
#include <tinyexr.h>

void file_io::saveImage(const std::string& filename, float* outputImage, const int& texWidth, const int& texHeight, OUTPUT_FORMAT format) {
	if (format == OUTPUT_FORMAT::EXR_B32G32R32 || format == OUTPUT_FORMAT::EXR_B16G16R16) {
		EXRHeader header;
		InitEXRHeader(&header);

		EXRImage image;
		InitEXRImage(&image);

		image.num_channels = 3;
		std::vector<float> images[3];
		images[0].resize(texWidth * texHeight);
		images[1].resize(texWidth * texHeight);
		images[2].resize(texWidth * texHeight);

		for (int i = 0; i < texWidth * texHeight; i++) {
			images[0][i] = outputImage[4 * i + 0];
			images[1][i] = outputImage[4 * i + 1];
			images[2][i] = outputImage[4 * i + 2];
		}

		float* image_ptr[3];
		image_ptr[0] = &(images[2].at(0)); // B
		image_ptr[1] = &(images[1].at(0)); // G
		image_ptr[2] = &(images[0].at(0)); // R

		image.images = (unsigned char**)image_ptr;
		image.width = texWidth;
		image.height = texHeight;

		header.num_channels = 3;
		header.channels = (EXRChannelInfo*)malloc(sizeof(EXRChannelInfo) * header.num_channels);
		// Must be BGR(A) order, since most of EXR viewers expect this channel order.
		strncpy(header.channels[0].name, "B", 255); header.channels[0].name[strlen("B")] = '\0';
		strncpy(header.channels[1].name, "G", 255); header.channels[1].name[strlen("G")] = '\0';
		strncpy(header.channels[2].name, "R", 255); header.channels[2].name[strlen("R")] = '\0';

		header.pixel_types = (int*)malloc(sizeof(int) * header.num_channels);
		header.requested_pixel_types = (int*)malloc(sizeof(int) * header.num_channels);
		header.compression_type == TINYEXR_COMPRESSIONTYPE_ZIP;
		for (int i = 0; i < header.num_channels; i++) {
			header.pixel_types[i] = TINYEXR_PIXELTYPE_FLOAT; // pixel type of input image
			if (format == OUTPUT_FORMAT::EXR_B32G32R32) {
				header.requested_pixel_types[i] = TINYEXR_PIXELTYPE_FLOAT; // pixel type of output image to be stored in .EXR
			}
			else {
				header.requested_pixel_types[i] = TINYEXR_PIXELTYPE_HALF;
			}

		}
		const char* err;
		int ret = SaveEXRImageToFile(&image, &header, (filename + ".exr").c_str(), &err);
		if (ret != TINYEXR_SUCCESS) {
			fprintf(stderr, "Save EXR err: %s\n", err);
			FreeEXRErrorMessage(err);
			throw std::runtime_error("failed to save EXR image!");
		}
		std::cout << "Framebuffer image saved to " << filename << ".exr" << std::endl;

		free(header.channels);
		free(header.pixel_types);
		free(header.requested_pixel_types);
	}
	else if (format == OUTPUT_FORMAT::HDR) {
		stbi_write_hdr((filename + ".hdr").c_str(), texWidth, texHeight, 4, outputImage);
		std::cout << "Framebuffer image saved to " << filename << ".hdr" << std::endl;

	}
	else if (format == OUTPUT_FORMAT::PNG_R8G8B8A8) {
		filename + ".png";
		stbi_write_png((filename + ".png").c_str(), texWidth, texHeight, 4, outputImage, 0);
		std::cout << "Framebuffer image saved to " << filename << ".png" << std::endl;
	}
}