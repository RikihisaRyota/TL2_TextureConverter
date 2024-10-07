#include "TextureConverter.h"

#include <assert.h>

void TextureConverter::ConvertTextureWICToDDS(const std::filesystem::path& path) {
	filePath_ = path;

	// WICテクスチャのロード
	auto hr = DirectX::LoadFromWICFile(filePath_.c_str(), DirectX::WIC_FLAGS_NONE, &metaData_, scratchImage_);
	assert(SUCCEEDED(hr));

	// DDS出力
	SaveDDSTextureToFile();
}

void TextureConverter::SaveDDSTextureToFile() {
	// 読み込んだテクスチャをSRGBとして扱う
	metaData_.format = DirectX::MakeSRGB(metaData_.format);
	// 拡張子を変更
	filePath_.replace_extension(L".dds");
	// DDSに書き出し
	auto hr = DirectX::SaveToDDSFile(scratchImage_.GetImages(),scratchImage_.GetImageCount(),metaData_,DirectX::DDS_FLAGS_NONE,filePath_.c_str());
	assert(SUCCEEDED(hr));
}

