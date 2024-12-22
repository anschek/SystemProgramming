#include <stdio.h>
#include <malloc.h>
#include <Windows.h>

#include <io.h>
#include <fcntl.h>

#define UNNAMED_PIPE_TASK 1

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

int _29_unnamedPipe(HANDLE hRead, HANDLE hWrite) {

	CloseHandle(hWrite);//закрываем дескриптор для записи у потомка
	readAndPrintToConsole(hRead);
	CloseHandle(hRead);
	return GetLastError();
}

int main(int argc, char* argv[])
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	HANDLE hRead, hWrite;//дескрипторы чтения и записи в анонимный канал
	switch (atoi(argv[0]))
	{
	case UNNAMED_PIPE_TASK:
		hWrite = (HANDLE)atoi(argv[1]);
		hRead = (HANDLE)atoi(argv[2]);
		return _29_unnamedPipe(hRead, hWrite);

	default:
		wprintf(L"Ошибка аргумента\n");
		return -1;
	}
	return 0;
}