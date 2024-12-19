
// 20. Создание и настройка проекта WinAPI. 
// Вывод сообщения в messagebox. 
// Текст сообщения считывается из текстового файла в кодировке Юникод

// 1. создание файла в папке проекта
// 2. открытие файла
// 3. считывание данных в массив широких символов
// 4. вывод сообщения в message box

#include "tasks.h"
#include <Windows.h>
#include <stdio.h>
#include <malloc.h>

int _20_messageBoxGromUtfFile_Test() {
	WCHAR* filePath = L"_20_text_for_mb.txt";

	HANDLE hFile = CreateFile(
		filePath,
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == -1) return errno;

	WCHAR* buffer = calloc(255, sizeof(WCHAR));
	int bufferSize = 255 * sizeof(WCHAR);
	int totalRead;
	BOOL success = ReadFile(
		hFile,
		buffer,
		bufferSize,
		&totalRead,
		NULL
	);
	if (!success) return errno;

	MessageBox(NULL, buffer, L"Текст из файла", MB_OK);
	return 0;
}