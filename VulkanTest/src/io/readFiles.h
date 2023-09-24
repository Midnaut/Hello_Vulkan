#pragma once
#include <vector>
#include <string>
#include <fstream>

static std::vector<char> ReadBinaryFile(const std::string& fileName) {
	// start reading at the end of the file to get size easily
	std::ifstream file(fileName, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + fileName + "!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	// reset the seek
	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();
	return buffer;
}