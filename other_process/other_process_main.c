#include <stdio.h>
#include <malloc.h>
#include <Windows.h>

#include <io.h>
#include <fcntl.h>

#define UNNAMED_PIPE_CLIENT 1
#define LAUNCH_SIMPLE_PROCESS 2
#define NAMED_PIPE_CLIENT 3
#define CLIPBOARD_COMMUNICATION 4


#define SIZE_BUFFER 256

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

int WriteToClipboard(LPWSTR str) {
	size_t strSize = (wcslen(str) + 1) * sizeof(WCHAR); // общий размер сообщения

	HANDLE hGlobalMemory = GlobalAlloc(GMEM_MOVEABLE, strSize); // выделенеи памяти в глобальной области
	memcpy(GlobalLock(hGlobalMemory), str, strSize); // копирование строки в глобальную память
	GlobalUnlock(hGlobalMemory); // вернуть доступ остальным к глобальной памяти

	OpenClipboard(0);
	EmptyClipboard(); // очистить
	SetClipboardData(CF_UNICODETEXT, hGlobalMemory); // записать данные формата текст юникода
	CloseClipboard();
	return 0;
}

LPWSTR ReadFromClipboard() {
	OpenClipboard(0);
	LPWSTR content = (LPWSTR)GetClipboardData(CF_UNICODETEXT); // прочитать данные формата текст юникода
	CloseClipboard();
	return content;
}

int main(int argc, char* argv[])
{
	HANDLE hRead, hWrite;//дескрипторы чтения и записи в анонимный канал

	// данные для именнованного канала
	LPCWSTR pipeName = L"//./pipe/MyPipe";
	WCHAR outBuffer[SIZE_BUFFER];
	WCHAR inBuffer[SIZE_BUFFER];
	int messageCounter = 0;
	HANDLE hPipe;
	BOOL successConnect;

	int clipboardMessageCount;
	LPWSTR serverClipboardMessage;

	switch (atoi(argv[1]))
	{
	case UNNAMED_PIPE_CLIENT:
		_setmode(_fileno(stdout), _O_U16TEXT);
		_setmode(_fileno(stdin), _O_U16TEXT);
		hWrite = (HANDLE)atoi(argv[1]);
		hRead = (HANDLE)atoi(argv[2]);
		return _29_unnamedPipe(hRead, hWrite);

	case LAUNCH_SIMPLE_PROCESS:
		for (int i = 0; i < argc; ++i) {
			printf("%s\n", argv[i]);
		}
		system("pause");
		return 100500;

	case NAMED_PIPE_CLIENT:
		_setmode(_fileno(stdout), _O_U16TEXT);
		_setmode(_fileno(stdin), _O_U16TEXT);
		while (TRUE) {
			hPipe = CreateFileW(
				pipeName,
				GENERIC_READ | GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				0,
				NULL
			);
			DWORD dwMode = PIPE_READMODE_MESSAGE; // режим работы канала
			successConnect = SetNamedPipeHandleState(
				hPipe,
				&dwMode,
				NULL,
				NULL
			);
			Sleep(500);
			if (!successConnect) {
				wprintf(L"(клиент) сервер не отвечает\n");
			}
			else {
				
				// сообщение серверу
				swprintf_s(outBuffer, SIZE_BUFFER, L"Сообщение серверу %d", ++messageCounter);
				WriteFile(
					hPipe,
					outBuffer,
					SIZE_BUFFER * sizeof(WCHAR),
					NULL,
					NULL
				);
				wprintf(L"(клиент) написал серверу: %s\n", outBuffer);
				ReadFile(hPipe, inBuffer, SIZE_BUFFER* sizeof(WCHAR), NULL, NULL);
				wprintf(L"(клиент) получил такой ответ сервера: %s\n", inBuffer);
			}
			CloseHandle(hPipe);
		}

	case CLIPBOARD_COMMUNICATION:
		_setmode(_fileno(stdout), _O_U16TEXT);
		_setmode(_fileno(stdin), _O_U16TEXT);

		clipboardMessageCount = 3;
		for (int i = 0; i < clipboardMessageCount; ++i) {
			serverClipboardMessage = ReadFromClipboard();
			wprintf(L"(процесс 2) процес 1 написал: %s\n", serverClipboardMessage);

			swprintf_s(outBuffer, SIZE_BUFFER, L"ОКей %d", i);
			WriteToClipboard(outBuffer);

			Sleep(5000);
		}
		break;

	default:
		wprintf(L"Ошибка аргумента\n");
		return -1;
	}
	return 0;
}