#include "TextureConverter.h"

#include <assert.h>

void TextureConverter::ConvertTextureWICToDDS(const std::filesystem::path& path) {
	filePath_ = path;

	// WIC�e�N�X�`���̃��[�h
	auto hr = DirectX::LoadFromWICFile(filePath_.c_str(), DirectX::WIC_FLAGS_NONE, &metaData_, scratchImage_);
	assert(SUCCEEDED(hr));

	// DDS�o��
	SaveDDSTextureToFile();
}

void TextureConverter::SaveDDSTextureToFile() {
	// �ǂݍ��񂾃e�N�X�`����SRGB�Ƃ��Ĉ���
	metaData_.format = DirectX::MakeSRGB(metaData_.format);
	// �g���q��ύX
	filePath_.replace_extension(L".dds");
	// DDS�ɏ����o��
	auto hr = DirectX::SaveToDDSFile(scratchImage_.GetImages(),scratchImage_.GetImageCount(),metaData_,DirectX::DDS_FLAGS_NONE,filePath_.c_str());
	assert(SUCCEEDED(hr));
}

