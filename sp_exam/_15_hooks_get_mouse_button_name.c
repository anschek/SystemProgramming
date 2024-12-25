
// 15. Обработка нажатия клавиши мыши в системе 
// (выписать в messagebox какая клавиша нажата и сколько раз)

// 1. Установка хука с функция формата HOOKPROC
// 2. Получение, интерпретация и передача сообщений
// Для основной функции
// 3. При коде <0 и возврате вызов следующего хука
// 4. Оюработка нажатий трех кнопок мыши из wParam и инкрементация

#include "tasks.h"
#include <Windows.h>
#include<stdio.h>
#include <malloc.h>
#include<io.h>
#include<fcntl.h>

int leftClickCount = 0;
int rightClickCount = 0;
int middleClickCount = 0;


LRESULT CALLBACK MouseButtonLog(int code, WPARAM wParam, LPARAM lParam) {
	if (code >= 0) {
		WCHAR* message = calloc(200, sizeof(WCHAR));
		switch (wParam) {
		case WM_LBUTTONDOWN:
			swprintf_s(message, 200, L"Левая: %d", ++leftClickCount);
			break;
		case WM_RBUTTONDOWN:
			swprintf_s(message, 200,  L"Правая: %d", ++rightClickCount);
			break;
		case WM_MBUTTONDOWN:
			swprintf_s(message, 200,  L"Средняя: %d", ++middleClickCount);
			break;
		}

		if (message[0] !=0) {
			MessageBoxW(NULL, message, L"Нажатие кнопки мыши", MB_OK);
		}
		free(message);
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}

int _15_hooksGetMouseButtonName_Test() {

	HHOOK hHook = SetWindowsHookExW(
		WH_MOUSE_LL,
		MouseButtonLog,
		NULL,
		0
	);
	if (!hHook) {
		wprintf(L"Ошибка устаноки хука: %lu\n", GetLastError());
		return -1;
	}
	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0) != WM_QUIT) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	UnhookWindowsHookEx(hHook);
	return 0;
}