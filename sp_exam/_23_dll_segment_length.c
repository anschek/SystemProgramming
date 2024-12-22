
// 23. Программа с импортом функции из файла DLL. Функция принимает  структуру, содержащую 
// координаты двух точек, а возвращает длину отрезка, который образуется этими точками 

// 1. Создание и настройка проекта dll
// 2. Объявление dllmain
// 3. Описание структур и функций
// 4. Импорт библиотеки
// 5. Создание сигнатур функций и их импорт из dll

#include "tasks.h"
#include<stdio.h>
#include <Windows.h>
#define DLL_PATH L"../x64/Debug/_23_dll.dll"

typedef struct Point {
	double x;
	double y;
} Point;

typedef double(*fun)(Point, Point);

int _23_dllSegmentLength_Test() {

	HINSTANCE dll = LoadLibrary(DLL_PATH);
	if (!dll) {
		wprintf(L"error : %d\n", GetLastError());
		return -1;
	}

	fun getDistance = GetProcAddress(dll, "getDistance");

	Point p1[] = { {0,0}, {0.5,0}, {-1,-1} };
	Point p2[] = { {0,1}, {1.5,1.5}, {2,2} };
	for (int i = 0; i < 3; ++i) {
		printf("result[%d]=%lf\n", i, getDistance(p1[i], p2[i]));
	}

	FreeLibrary(dll);
	return 0;
}
