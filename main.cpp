#include <cstdio>
#include <cstdlib>
#include <assert.h>

#include "Externals/DirectXTex/DirectXTex.h"

#include "Src/TextureConverter.h"

enum Argument {
	kApplicationPath,
	kFilePath,

	kNumArgument,
};

int main(int argc, char* argv[]) {

	assert(argc >= kNumArgument);

	// COM���C�u����������
	auto hr = CoInitializeEx(nullptr,COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	TextureConverter converter;
	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	// COM���C�u�����I��
	CoUninitialize();

	system("pause");
	return 0;
}