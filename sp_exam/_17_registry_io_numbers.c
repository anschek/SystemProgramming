
// 17. Запись и считывание числовых параметров в системный реестр

// 1. определиться с веткой, именем и значением параметра
// 2. записать параметру значение с приведением к константным байтам
// 3. определить буфер и его размер, считать
// 4. удалить параметр
// 5. закрыть дескриптор ключа

#include "tasks.h"
#include <Windows.h>
#include <stdio.h>

#include<io.h>
#include<fcntl.h>

int _17_registryInOutNumbers_Test() {
	HKEY hKey = NULL;
	LPCWSTR keyName = L"testKey";
	LPCWSTR valueName = L"testValue";
	DWORD valueData = 12345;

	LSTATUS status = 0;
	status = RegCreateKey(HKEY_CURRENT_USER, keyName, &hKey);
	if (status != ERROR_SUCCESS) return status;

	status = RegSetValueEx(
		hKey, 
		valueName, 
		0,						// зарезервированно
		REG_DWORD,				// тип данных
		(const BYTE*)&valueData,// что записать 
		sizeof(DWORD));			// выделяемая память
	if (status != ERROR_SUCCESS) return status;
	wprintf(L"sucess write\n");


	DWORD buffer;
	DWORD bufferSize = sizeof(DWORD);
	status = RegQueryValueEx(
		hKey, 
		valueName, 
		NULL,				// зарезервированно
		NULL,				// тип
		(const BYTE*)&buffer,// куда записывать
		&bufferSize);		 // размер буфера
	if (status != ERROR_SUCCESS) return status;
	wprintf(L"data: %d\n", buffer);

	status = RegDeleteValue(hKey, valueName);
	if (status != ERROR_SUCCESS) return status;
	wprintf(L"sucess deleting\n");

	status = RegCloseKey(hKey);
	if (status != ERROR_SUCCESS) return status;
	wprintf(L"sucess close\n");
	return 0;
}