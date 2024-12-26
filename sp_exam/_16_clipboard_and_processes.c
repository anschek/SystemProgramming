
// 16. Использование системного буфера обмена для передачи строковых значений между процессами

// 1. создание функций чтении и записи для буфера
// 2. отправка сообщений в другой процесс, чтение ответов
// 3. другой процесс делает то же самое

#include "tasks.h"
#include <stdio.h>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

int WriteToClipboard_Proc(LPWSTR str) {
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

LPWSTR ReadFromClipboard_Proc() {
	OpenClipboard(0);
	LPWSTR content = (LPWSTR)GetClipboardData(CF_UNICODETEXT); // прочитать данные формата текст юникода
	CloseClipboard();
	return content;
}

int _16_clipboardForProcessesCommunication_Test() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	int messageCount = 3;
	int bufferSize = 256;
	LPWSTR outBuffer;
	for (int i = 0; i < messageCount; ++i) {
		outBuffer = calloc(bufferSize, sizeof(WCHAR));
		swprintf_s(outBuffer, bufferSize, L"сообщение сервера %d", i);
		WriteToClipboard_Proc(outBuffer);
		free(outBuffer);
		Sleep(5000);
		LPWSTR response = ReadFromClipboard_Proc();
		wprintf(L"(процесс 1) прроцесс 2 отвтеил: %s\n", response);
	}
	wprintf(L"конец работы\n");
	return 0;
}