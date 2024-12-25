
// 7. Получение кода клавиши в формате ASCII и использованием Windows HOOK. 
// Название клавиши выводить в MessageBox

// 1. Установка хука с функция формата HOOKPROC
// 2. Получение, интерпретация и передача сообщений
// Для основной функции
// 3. При коде <0 и возврате вызов следующего хука
// 4. Опредления действий при wParam==нажатие клавиши
// 5. Преобразование структуры lParam
// 6. Получение виртуальной клавиши по полю структуры с макросом: virtual key to char
// 7. Определение сообщения для ascii и вывод

#include "tasks.h"
#include <stdio.h>
#include <Windows.h>
#include <malloc.h>

LRESULT CALLBACK LogAsciiKey(int code, WPARAM wParam, LPARAM lParam) {
	if (code < 0) {
		CallNextHookEx(NULL, code, wParam, lParam);
	}

	if (wParam == WM_KEYDOWN) {
		PKBDLLHOOKSTRUCT pHook = (PKBDLLHOOKSTRUCT)lParam;
		char asciiCode = MapVirtualKeyA(pHook->vkCode, MAPVK_VK_TO_CHAR);

		int messageSize = 256;
		char* message = calloc(messageSize, sizeof(char));

		if (asciiCode >= ' ' && asciiCode <= '~') {
			sprintf_s(message, messageSize, "ascii symbol:%c with vkCode:%d", asciiCode, pHook->vkCode);
		}
		else {
			sprintf_s(message, messageSize, "non-ascii symbol with vkCode:%d", pHook->vkCode);
		}
		MessageBoxA(NULL, message, "Key pressed", MB_OK);
		free(message);
	}

	return CallNextHookEx(NULL, code, wParam, lParam);
}

int _7_hooksGetAsciiKey_Test() {

	HHOOK hHook = SetWindowsHookExA(
		WH_KEYBOARD_LL,
		LogAsciiKey,
		NULL,
		0
	);

	if (!hHook) {
		printf("error of create hook: %lu", GetLastError());
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