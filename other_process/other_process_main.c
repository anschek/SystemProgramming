#include "tasks.h"
#include <stdio.h>
#include <malloc.h>
#include <Windows.h>

#include <io.h>
#include <fcntl.h>

#define UNNAMED_PIPE_CLIENT 1
#define LAUNCH_SIMPLE_PROCESS 2
#define NAMED_PIPE_CLIENT 3
#define CLIPBOARD_COMMUNICATION 4


int main(int argc, char* argv[])
{
	HANDLE hRead, hWrite;//дескрипторы чтения и записи в анонимный канал

	switch (atoi(argv[1]))
	{
	case UNNAMED_PIPE_CLIENT:
		hWrite = (HANDLE)atoi(argv[1]);
		hRead = (HANDLE)atoi(argv[2]);
		return _29_unnamedPipe_OtherProcess(hRead, hWrite);

	case LAUNCH_SIMPLE_PROCESS:
		for (int i = 0; i < argc; ++i) {
			printf("%s\n", argv[i]);
		}
		system("pause");
		return 100500;

	case NAMED_PIPE_CLIENT:
		return _24_namedPipe_OtherProcess();

	case CLIPBOARD_COMMUNICATION:
		return _16_clipboardCommunication_OtherProcess();

	default:
		wprintf(L"Ошибка аргумента\n");
		return -1;
	}
	return 0;
}