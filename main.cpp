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
	// �R�}���h���C�������w��Ȃ�
	if (argc < Argument::kNumArgument) {
		// �g�����̕\��
		TextureConverter::OutPutUsage();
		return 0;
	}

	// COM���C�u����������
	auto hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	// �I�v�V������
	int numOptions = argc - Argument::kNumArgument;
	// �I�v�V�����z��
	char** options = argv + Argument::kNumArgument;

	TextureConverter converter;
	converter.ConvertTextureWICToDDS(argv[Argument::kFilePath], numOptions, options);

	// COM���C�u�����I��
	CoUninitialize();

	//system("pause");
	return 0;
}