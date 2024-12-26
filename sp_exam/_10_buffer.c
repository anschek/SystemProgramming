
// 10. Программа для записи и считывание строки с использованием системного буфера

// Для записи
// 1. Определить размер данных, выделить под них место в глобальной памяти
// 2. Открыть, очистить, записать, закрыть

// Для чтения
// 3. Открыть, прочитать, закрыть

#include "tasks.h"
#include <stdio.h>
#include <Windows.h>

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


int _10_clipboardInOutStrings_Test() {
	WriteToClipboard(L"Новый текст должен быть доступен из системного буфера обмена");
	LPWSTR clipboardContent = ReadFromClipboard();
	MessageBox(NULL, clipboardContent, L"В буфере было записано", MB_OK);
	return 0;
}