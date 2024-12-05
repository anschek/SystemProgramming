
// 1.Создание и отладка библиотеки DLL. 
// Для демонстрации работы написать две элементарные функции в библиотеке и вызвать их из основной программы.




//		на стороне dll
// 1. общие/ тип конфигурации/ динамическая библиотека
// 2. определние точки входа DllMain
// 3. созданий функций экспорта

//		на стороне вызова
// 4. объявление типов функций
// 5. вызов библиотеки через LoadLibrary
// 6. импорт функций
// 7. вызов
// 8. высвобождение памяти от библиотеки

#include"_1_dll.h"
#include <stdio.h>
#include <Windows.h>
#define PATH L"_1_dll.dll"

typedef int(*fun1)(LPWSTR);
typedef DWORD(*fun2)(DWORD, DWORD);

int _1_dll_Test() {
	HINSTANCE dll = LoadLibraryW(PATH);

	if (!dll) {
		printf("error : %d\n", GetLastError());
		return 1;
	}

	// получение адреса функций
	fun1 fun1_object = GetProcAddress(dll, "Hello");
	fun2 fun2_object = GetProcAddress(dll, "Sum");

	fun1_object(L"Привет, мир");
	printf("%d", fun2_object(2, 6));

	FreeLibrary(dll);

	return 0;
};