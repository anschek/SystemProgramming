#include "tasks.h"
#include <stdio.h>
#include <malloc.h>
#include <Windows.h>

#include <io.h>
#include <fcntl.h>

void readAndPrintToConsole(HANDLE hRead) {
	WCHAR* buffer = calloc(255, sizeof(WCHAR));
	while (
		ReadFile(//читаем данные из канала
			hRead,
			buffer,
			255 * sizeof(WCHAR),
			NULL,
			NULL)
		) {
		wprintf(L"ребенок прочел: %s\n", buffer);//выводим на экран и завершаем работу
		memset(buffer, 0, 255 * sizeof(WCHAR));
	}
	free(buffer);
}

int _29_unnamedPipe_OtherProcess(HANDLE hRead, HANDLE hWrite) {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	CloseHandle(hWrite);//закрываем дескриптор для записи у потомка
	readAndPrintToConsole(hRead);
	CloseHandle(hRead);

	return GetLastError();
}