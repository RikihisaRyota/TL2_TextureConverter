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

	assert(argc >= kNumArgument);
	for (int i = 0; i < argc; i++) {
		printf(argv[i]);
		printf("\n");
	}

	// COMライブラリ初期化
	auto hr = CoInitializeEx(nullptr,COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	TextureConverter converter;
	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	// COMライブラリ終了
	CoUninitialize();

	system("pause");
	return 0;
}