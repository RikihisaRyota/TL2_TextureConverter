#pragma once

#include <filesystem>

#include "../Externals/DirectXTex/DirectXTex.h"

class TextureConverter {
public:
    // WIC����DDS��
    void ConvertTextureWICToDDS(const std::filesystem::path& path);
private:
    // DDS�e�N�X�`���Ƃ��ăt�@�C�������o��
    void SaveDDSTextureToFile();
    // �摜���
    DirectX::TexMetadata metaData_;
    // �摜�C���[�W�̃R���e�i
    DirectX::ScratchImage scratchImage_;
    // filePath
    std::filesystem::path filePath_;
};