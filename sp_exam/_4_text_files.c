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

HANDLE Open(LPCWSTR file_name, DWORD desired_access) {
	return CreateFileW(
		file_name,
		desired_access,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
}

int Read(HANDLE file_handle, LPWSTR buffer, size_t buffer_count) {
	int bytes_read; // сколько удалось считать байтов
	ReadFile(
		file_handle,
		buffer,
		buffer_count * sizeof(WCHAR),
		&bytes_read,
		NULL
	);
	return bytes_read;
}

int Write(HANDLE file_handle, LPWSTR buffer) {
	int bytes_write; // сколько удалось считать байтов
	WriteFile(
		file_handle,
		buffer,
		wcslen(buffer) * sizeof(WCHAR),
		&bytes_write,
		NULL
	);
	return bytes_write;
}

int ChangeFilePosition(HANDLE file_handle, DWORD move_method) {
	return SetFilePointer(
		file_handle,
		NULL,
		NULL,
		move_method
	);
}

int _4_textFiles_Test() {
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
	int buffer_count = 100;
	LPWSTR buffer = calloc(buffer_count, sizeof(WCHAR));
	int bytes_read = Read(input, buffer, buffer_count);
	wprintf(L"%d bytes: %s\n", bytes_read, buffer);

	if (bytes_read == 0) return -1;

	// записываем во второй (для добавления данных смещаем позицию)
	int output_offset = ChangeFilePosition(output, FILE_END);
	if (output_offset == INVALID_SET_FILE_POINTER) {
		wprintf(L"Ошибка установки курсора: %d\n", GetLastError());
		return -1;
	}
	
	int bytes_write = Write(output, buffer);
	wprintf(L"%d bytes", bytes_write);
	if (bytes_write == 0) return -1;

	// закрытие дескрипторов
	CloseHandle(input);
	CloseHandle(output);
	return 0;
};