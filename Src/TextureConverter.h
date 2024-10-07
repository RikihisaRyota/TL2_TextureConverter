#pragma once

#include <filesystem>

#include "../Externals/DirectXTex/DirectXTex.h"

class TextureConverter {
public:
    // WICからDDSへ
    void ConvertTextureWICToDDS(const std::filesystem::path& path);
private:
    // DDSテクスチャとしてファイル書き出し
    void SaveDDSTextureToFile();
    // 画像情報
    DirectX::TexMetadata metaData_;
    // 画像イメージのコンテナ
    DirectX::ScratchImage scratchImage_;
    // filePath
    std::filesystem::path filePath_;
};