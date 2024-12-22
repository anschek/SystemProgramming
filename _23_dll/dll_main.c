
#include <Windows.h>
#include <process.h> // сигнатура функции
#include<winnt.h> // объявление макросов
#include <stdio.h>
#include <math.h>

BOOL __stdcall DllMain(
    _In_     void* _DllHandle,
    _In_     unsigned long _Reason,
    _In_opt_ void* _Reserved
){
	// lpReserved используется для передачи дополнительных данных
	BOOL bSuccess = TRUE;
	switch (_Reason) // код события
	{
	case DLL_PROCESS_ATTACH: // Инициализацяи
		MessageBoxW(NULL, L"успешно", L"DLL_PROCESS_ATTACH", MB_OK);
		break;
	case DLL_THREAD_ATTACH: // Поток подключен
		MessageBoxW(NULL, L"успешно", L"DLL_THREAD_ATTACH", MB_OK);
		break;
	case DLL_THREAD_DETACH: // Поток отключен
		MessageBoxW(NULL, L"успешно", L"DLL_THREAD_DETACH", MB_OK);
		break;
	case DLL_PROCESS_DETACH: // Освобождение ресурсов
		MessageBoxW(NULL, L"успешно", L"DLL_PROCESS_DETACH", MB_OK);
		break;
	}
	return bSuccess;
}

typedef struct Point {
	double x;
	double y;
} Point;

__MIDL_DECLSPEC_DLLEXPORT double getDistance(Point p1, Point p2) {
	return sqrt(
		pow(p1.x - p2.x, 2) +
		pow(p1.y - p2.y, 2)
	);
}