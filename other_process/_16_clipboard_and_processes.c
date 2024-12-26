
#include "tasks.h"
#include <stdio.h>
#include <Windows.h>

#include <io.h>
#include <fcntl.h>
#define SIZE_BUFFER 256

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

int _16_clipboardCommunication_OtherProcess() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	int clipboardMessageCount = 3;
	LPWSTR serverClipboardMessage;
	WCHAR outBuffer[SIZE_BUFFER];

	for (int i = 0; i < clipboardMessageCount; ++i) {
		serverClipboardMessage = ReadFromClipboard();
		wprintf(L"(процесс 2) процес 1 написал: %s\n", serverClipboardMessage);

		swprintf_s(outBuffer, SIZE_BUFFER, L"ОКей %d", i);
		WriteToClipboard(outBuffer);

		Sleep(5000);
	}
}