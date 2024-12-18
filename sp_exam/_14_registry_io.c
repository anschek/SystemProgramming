
// 14. Запись и считывание строковых параметров в системный реестр

// 1. определиться с веткой и именем параметра
// 2. записать параметру значение
// 3. считать
// 4. вывести (изменить настройки консоли)
// 5. удалить параметр (ключ)
// 6. если были открыты дескрипторы, закрыть их

#include "tasks.h"
#include <Windows.h>
#include <stdio.h>
#include <malloc.h>
// для юникода
#include <io.h>
#include <fcntl.h>

int _14_registryInOutStrings_Test() {
	HKEY hKey = NULL;
	LPCWSTR valueName = L"testValue";
	LPCWSTR valueData = L"Тестовое значение параметра";

	LSTATUS status = 0;

	status = RegSetValue(HKEY_CURRENT_USER, valueName, REG_SZ, valueData, wcslen(valueData) * sizeof(WCHAR));
	if (status != ERROR_SUCCESS) return status;

	WCHAR* buffer = calloc(255, sizeof(WCHAR));
	DWORD bufferSize = 255 *  sizeof(WCHAR);
	status = RegGetValue(
		HKEY_CURRENT_USER,      
		valueName,			// Путь к ключу
		NULL,				// Дополнительное имя параметра (если есть часть пути)
		RRF_RT_REG_SZ,		// Тип ожидаемых данных
		NULL,				// Фактический тип данных (можно NULL)
		buffer,				// Буфер
		&bufferSize			// указатель на размер буфера	
	);
	if (status != ERROR_SUCCESS) return status;

	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(L"data: %s\n", buffer);

	status = RegDeleteKey(HKEY_CURRENT_USER, valueName);
	if (status != ERROR_SUCCESS) return status;
	wprintf(L"sucess deleting\n", buffer);
	return 0;
}