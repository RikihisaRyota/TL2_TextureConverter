#pragma once

#include <filesystem>

#include "../Externals/DirectXTex/DirectXTex.h"

class TextureConverter {
public:
	// 使用方法を出力する
	static void OutPutUsage();
	// WICからDDSへ
	void ConvertTextureWICToDDS(const std::filesystem::path& path, int numOptions = 0, char* options[] = nullptr);
private:
	// DDSテクスチャとしてファイル書き出し
	void SaveDDSTextureToFile(int numOptions, char* options[]);
	// 画像情報
	DirectX::TexMetadata metaData_;
	// 画像イメージのコンテナ
	DirectX::ScratchImage scratchImage_;
	// filePath
	std::filesystem::path filePath_;
};