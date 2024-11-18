#include "TextureConverter.h"

#include <string>
#include <assert.h>

void TextureConverter::OutPutUsage() {
	printf("画像ファイルをWIC形式からDDS形式に変換します\n");
	printf("\n");
	printf("TextureConverter [ドライブ:][パス][ファイル名][-ml level]\n");
	printf("\n");
	printf("[ドライブ:][パス][ファイル名]: 変換したいWIC形式の画像ファイルを指定します\n");
	printf("[-ml level]ミップレベルを指定しまう。０を指定すると１ｘ１のフルミップマップチェーンを生成します\n");
}

void TextureConverter::ConvertTextureWICToDDS(const std::filesystem::path& path, int numOptions, char* options[]) {
	filePath_ = path;
	// WICテクスチャのロード
	auto hr = DirectX::LoadFromWICFile(filePath_.c_str(), DirectX::WIC_FLAGS_NONE, &metaData_, scratchImage_);
	assert(SUCCEEDED(hr));

	// DDS出力
	SaveDDSTextureToFile(numOptions, options);
}

void TextureConverter::SaveDDSTextureToFile(int numOptions, char* options[]) {
	size_t mipLevel = 0;
	// ミップレベル指定を検索
	for (int i = 0; i < numOptions; i++) {
		if (std::string(options[i]) == "-ml") {
			// ミップレベル指定
			mipLevel = std::stoi(options[i + 1]);
			break;
		}
	}
	// ミップマップ生成
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

	// 圧縮形式に変換
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

	// 読み込んだテクスチャをSRGBとして扱う
	metaData_.format = DirectX::MakeSRGB(metaData_.format);
	// 拡張子を変更
	filePath_.replace_extension(L".dds");
	// DDSに書き出し
	hr = DirectX::SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metaData_, DirectX::DDS_FLAGS_NONE, filePath_.c_str());
	assert(SUCCEEDED(hr));
}

