#pragma once

#include <filesystem>

class TextureConverter {
public:
    // WIC����DDS��
    void ConvertTextureWICToDDS(const std::filesystem::path& path);
private:
};