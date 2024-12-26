
#include "tasks.h"
#include <stdio.h>
#include <malloc.h>
#include <Windows.h>

#include <io.h>
#include <fcntl.h>

#define SIZE_BUFFER 256

int _24_namedPipe_OtherProcess() {
	LPCWSTR pipeName = L"//./pipe/MyPipe";
	WCHAR outBuffer[SIZE_BUFFER];
	WCHAR inBuffer[SIZE_BUFFER];
	int messageCounter = 0;
	HANDLE hPipe;
	BOOL successConnect;

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
			ReadFile(hPipe, inBuffer, SIZE_BUFFER * sizeof(WCHAR), NULL, NULL);
			wprintf(L"(клиент) получил такой ответ сервера: %s\n", inBuffer);
		}
		CloseHandle(hPipe);
	}
	return 0;
}