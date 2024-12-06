// 4. Программа для считывания и записи строкового значения из текстового файла с последующей записью его в другой текстовый файл. 
// Для работы с файлами используются функции WinAPI.


// 1. создать файлы для чтения и записи. Они должны распологаться в папке проекта (не решения). 
// В входном файле записать строку. Кодировка файлов должна быть utf-16 le
// 2. создание функции открытия, как создание с диспозицией OPEN_EXISTING
// 3. создание функции чтения
// 4. создание функции записи
// 5. закрытие файлов
// *6. если необходимо вывести на консоль - смена кодировки консоли


#include"tasks.h"
#include<stdio.h>
#include<malloc.h>
#include<Windows.h>
// для юникода
#include <io.h>
#include <fcntl.h>

HANDLE Open(LPCWSTR fileName, DWORD desiredAccess) {
	return CreateFileW(
		fileName,
		desiredAccess,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
}

int Read(HANDLE fileHandle, LPWSTR buffer, size_t bufferCount) {
	int bytesRead; // сколько удалось считать байтов
	ReadFile(
		fileHandle,
		buffer,
		bufferCount * sizeof(WCHAR),
		&bytesRead,
		NULL
	);
	return bytesRead;
}

int Write(HANDLE hFile, LPWSTR buffer) {
	int bytesWrite; // сколько удалось считать байтов
	WriteFile(
		hFile,
		buffer,
		wcslen(buffer) * sizeof(WCHAR),
		&bytesWrite,
		NULL
	);
	return bytesWrite;
}

int ChangeFilePosition(HANDLE fileHandle, DWORD moveMethod) {
	return SetFilePointer(
		fileHandle,
		NULL,
		NULL,
		moveMethod
	);
}

int _4_text_files_Test() {
	// Устанавливаем кодовую страницу консоли на UTF-16
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	// открываем файлы
	HANDLE input = Open(L"input.txt", GENERIC_READ);
	HANDLE output = Open(L"output.txt", FILE_APPEND_DATA); // можно использовать generic_write для записи с нуля

	if (input == -1 || output == -1) {
		wprintf(L"Ошибка открытия файлов: %d\n", GetLastError());
		return -1;
	}

	// читаем из первого
	int bufferCount = 100;
	LPWSTR buffer = calloc(bufferCount, sizeof(WCHAR));
	int bytesRead = Read(input, buffer, bufferCount);
	wprintf(L"%d bytes: %s\n", bytesRead, buffer);

	if (bytesRead == 0) return -1;

	// записываем во второй (для добавления данных смещаем позицию)
	int outputOffset = ChangeFilePosition(output, FILE_END);
	if (outputOffset == INVALID_SET_FILE_POINTER) {
		wprintf(L"Ошибка установки курсора: %d\n", GetLastError());
		return -1;
	}
	
	int bytesWrite = Write(output, buffer);
	wprintf(L"%d bytes", bytesWrite);
	if (bytesWrite == 0) return -1;

	// закрытие дескрипторов
	CloseHandle(input);
	CloseHandle(output);
	return 0;
};