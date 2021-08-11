#pragma once


std::string;

enum class OUTPUT_FORMAT
{
	EXR_B32G32R32, EXR_B16G16R16, HDR, PNG_R8G8B8A8
};

namespace file_io {
	void saveImage(const std::string& filname, float* outputImage, const int& texWidth, const int& texHeight, OUTPUT_FORMAT format);
}