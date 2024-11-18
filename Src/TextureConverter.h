#pragma once

#include <filesystem>

#include "../Externals/DirectXTex/DirectXTex.h"

class TextureConverter {
public:
	// �g�p���@���o�͂���
	static void OutPutUsage();
	// WIC����DDS��
	void ConvertTextureWICToDDS(const std::filesystem::path& path, int numOptions = 0, char* options[] = nullptr);
private:
	// DDS�e�N�X�`���Ƃ��ăt�@�C�������o��
	void SaveDDSTextureToFile(int numOptions, char* options[]);
	// �摜���
	DirectX::TexMetadata metaData_;
	// �摜�C���[�W�̃R���e�i
	DirectX::ScratchImage scratchImage_;
	// filePath
	std::filesystem::path filePath_;
};