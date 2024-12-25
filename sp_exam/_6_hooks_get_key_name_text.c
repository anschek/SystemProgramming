
// 6. Получение названия клавиши с использованием функции GetKeyNameText (Windows HOOK). 
// Название клавиши выводить в MessageBox

// 1. Установка хука с функция формата HOOKPROC
// 2. Получение, интерпретация и передача сообщений
// Для основной функции
// 3. При коде <0 и возврате вызов следующего хука
// 4. Опредления действий при wParam==нажатие клавиши
// 5. Преобразование структуры lParam
// 6. Получение виртуальной клавиши по полю структуры, сдвиг влево на 16 бит (освобождение служебной информации)
// 7. Если символ больше 32 (space), они печатны, установка 24 бита
// 8. Получение имени клавиши и текущей раскладки
// 9. Если раскладка 1049 (русская) , а клавиша печатна (1 символ) - надо изменить значение по таблице имен
// 10. Вывод в message box

#include "tasks.h"
#include <stdio.h>
#include <Windows.h>
#include <malloc.h>

#include <io.h>
#include <fcntl.h>

#define RUS 1049

// Таблица сопоставлений английских символов русским
WCHAR EnToRus(WCHAR c) {
    wchar_t enKeys[] = L"QWERTYUIOP[]ASDFGHJKL;'ZXCVBNM,./";
    wchar_t ruKeys[] = L"ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ.";

    // Проходим по всем символам английской раскладки
    for (size_t i = 0; i < wcslen(enKeys); i++) {
        if (c == enKeys[i])
            return ruKeys[i]; // Возвращаем соответствующий символ
        
    }
    
    return c;// Если символ не найден в таблице, возвращаем его как есть
}

LRESULT CALLBACK LogKey(int code, WPARAM wParam, LPARAM lParam) {
	if (code < 0) {
		CallNextHookEx(NULL, code, wParam, lParam); // Передача сообщения следующему хуку
	}

	if (wParam == WM_KEYDOWN) {
		PKBDLLHOOKSTRUCT pHook = (PKBDLLHOOKSTRUCT)lParam;
		int bufferSize = 256;
		WCHAR* keyName = calloc(bufferSize, sizeof(WCHAR));

		// Получаем код клавиши
		DWORD iKey = MapVirtualKeyW(pHook->vkCode, 0) << 16; // 0-15 биты отводятся под служебную информацию
				
		if (pHook->vkCode > 32) {// Определяем печатаемые символы
			iKey |= 1 << 24; // Устанавливаем 24-й бит, чтобы клавиша обрабатывалась как печатная (расширенная)
		}
				
		// Получаем название клавиши
		GetKeyNameTextW(iKey, keyName, bufferSize);		 

		// Получаем раскладку клавиатуры
		WORD keyboardLayout = GetKeyboardLayout(0);
		
		wprintf(L"len: %d key: %d\n", wcslen(keyName), keyboardLayout);

		// Если нажата печатная клавиша
        if (wcslen(keyName) == 1) {

            // Обрабатываем кириллицу
            if (keyboardLayout == RUS) {
				wprintf(L"before %c\n", keyName[0]);
                keyName[0] = EnToRus(keyName[0]);
				wprintf(L"after %c\n", keyName[0]);
            }
        }

		MessageBoxW(NULL, keyName, L"Нажата клавиша", MB_OK);
		free(keyName);
	}

	return CallNextHookEx(NULL, code, wParam, lParam);// Передача сообщения следующему хуку
}

int  _6_hooksGetKeyNameText_Test() {
	_setmode(_fileno(stdout), _O_U16TEXT);

	HHOOK newHook = SetWindowsHookExW(
		WH_KEYBOARD_LL,
		LogKey,
		NULL,
		0
	);

	if (!newHook) {
		wprintf(L"Ошибка установки хука: %lu\n", GetLastError());
		return -1;
	}

	// Обработка сообщений
	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0) != WM_QUIT) { // извлечение сообщений из очереди
		TranslateMessage(&msg); // Преобразование нажатий клавиш в символы
		DispatchMessageW(&msg);  // Передача сообщения следующей процедуре
	}

	// Удаление хука
	UnhookWindowsHookEx(newHook);

	return 0;
}