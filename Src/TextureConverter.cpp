#include "TextureConverter.h"

#include <string>
#include <assert.h>

void TextureConverter::OutPutUsage() {
	printf("�摜�t�@�C����WIC�`������DDS�`���ɕϊ����܂�\n");
	printf("\n");
	printf("TextureConverter [�h���C�u:][�p�X][�t�@�C����][-ml level]\n");
	printf("\n");
	printf("[�h���C�u:][�p�X][�t�@�C����]: �ϊ�������WIC�`���̉摜�t�@�C�����w�肵�܂�\n");
	printf("[-ml level]�~�b�v���x�����w�肵�܂��B�O���w�肷��ƂP���P�̃t���~�b�v�}�b�v�`�F�[���𐶐����܂�\n");
}

void TextureConverter::ConvertTextureWICToDDS(const std::filesystem::path& path, int numOptions, char* options[]) {
	filePath_ = path;
	// WIC�e�N�X�`���̃��[�h
	auto hr = DirectX::LoadFromWICFile(filePath_.c_str(), DirectX::WIC_FLAGS_NONE, &metaData_, scratchImage_);
	assert(SUCCEEDED(hr));

	// DDS�o��
	SaveDDSTextureToFile(numOptions, options);
}

void TextureConverter::SaveDDSTextureToFile(int numOptions, char* options[]) {
	size_t mipLevel = 0;
	// �~�b�v���x���w�������
	for (int i = 0; i < numOptions; i++) {
		if (std::string(options[i]) == "-ml") {
			// �~�b�v���x���w��
			mipLevel = std::stoi(options[i + 1]);
			break;
		}
	}
	// �~�b�v�}�b�v����
	DirectX::ScratchImage mipChain{};
	auto hr = DirectX::GenerateMipMaps(
		scratchImage_.GetImages(),
		scratchImage_.GetImageCount(),
		scratchImage_.GetMetadata(),
		DirectX::TEX_FILTER_DEFAULT,
		mipLevel,
		mipChain
	);

	if (SUCCEEDED(hr)) {
		scratchImage_ = std::move(mipChain);
		metaData_ = scratchImage_.GetMetadata();
	}

	// ���k�`���ɕϊ�
	DirectX::ScratchImage converted{};
	hr = DirectX::Compress(
		scratchImage_.GetImages(),
		scratchImage_.GetImageCount(),
		metaData_, DXGI_FORMAT_BC7_UNORM_SRGB,
		DirectX::TEX_COMPRESS_BC7_QUICK | DirectX::TEX_COMPRESS_SRGB_OUT | DirectX::TEX_COMPRESS_PARALLEL,
		1.0f,
		converted);

	if (SUCCEEDED(hr)) {
		scratchImage_ = std::move(converted);
		metaData_ = scratchImage_.GetMetadata();
	}

	// �ǂݍ��񂾃e�N�X�`����SRGB�Ƃ��Ĉ���
	metaData_.format = DirectX::MakeSRGB(metaData_.format);
	// �g���q��ύX
	filePath_.replace_extension(L".dds");
	// DDS�ɏ����o��
	hr = DirectX::SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metaData_, DirectX::DDS_FLAGS_NONE, filePath_.c_str());
	assert(SUCCEEDED(hr));
}

