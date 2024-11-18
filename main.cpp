#include <cstdio>
#include <cstdlib>
#include <assert.h>

#include "Src/TextureConverter.h"

enum Argument {
	kApplicationPath,
	kFilePath,

	kNumArgument,
};

int main(int argc, char* argv[]) {

	assert(argc >= Argument::kNumArgument);
	for (int i = 0; i < argc; i++) {
		printf(argv[i]);
		printf("\n");
	}
	// コマンドライン引数指定なし
	if (argc < Argument::kNumArgument) {
		// 使い方の表示
		TextureConverter::OutPutUsage();
		return 0;
	}

	// COMライブラリ初期化
	auto hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	// オプション数
	int numOptions = argc - Argument::kNumArgument;
	// オプション配列
	char** options = argv + Argument::kNumArgument;

	TextureConverter converter;
	converter.ConvertTextureWICToDDS(argv[Argument::kFilePath], numOptions, options);

	// COMライブラリ終了
	CoUninitialize();

	//system("pause");
	return 0;
}