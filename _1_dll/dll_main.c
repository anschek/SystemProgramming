#include <Windows.h>

__declspec(dllexport) int Hello(LPWSTR str);
int Hello(LPWSTR str) {
	return MessageBoxW(NULL, str, L"DLL_FUNCTION_CALL", MB_OK);
}

__declspec(dllexport) int Sum(DWORD lhs, DWORD rhs);
DWORD Sum(DWORD lhs, DWORD rhs) {
	return lhs + rhs;
}

BOOL WINAPI DllMain(HINSTANCE hInstDll, DWORD dwReason, LPVOID lpReserved) {
	// lpReserved используется для передачи дополнительных данных
	BOOL bSuccess = TRUE;
	switch (dwReason) // код события
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