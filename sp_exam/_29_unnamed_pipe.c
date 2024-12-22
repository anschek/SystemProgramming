
// 29. Использование анонимного канала для передачи строковых значений между процессами

// 1. подготовка данных для создания канала
// 2. создание канала
// 3. подготовка данных для создания процесса
// 4. создание процесса (клиента)

// на сервере:
// 5. отпрвка сообщений и паузы межлу ними
// 6. ожидание дочернего процесса, получение кода возврата, очистка памяти

// на клиенте:
// 7. парсинг аргументов в дескрипторы
// 8. чтение и вывод на консоль


#define _CRT_SECURE_NO_WARNINGS
#include "tasks.h"
#include <stdio.h>
#include <Windows.h>
#include<io.h>
#include<fcntl.h>

int _29_unnamedPipe_Test() {

	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	
	LPCWSTR otherProcessPath = L"..\\x64\\Debug\\other_process.exe";

	HANDLE hRead, hWrite; // дескрипторы чтениЯ и записи в канал

	SECURITY_ATTRIBUTES sa = { // структура безопасности
		sizeof(sa), // длина
		NULL,		// дескриптор безопасности
		TRUE		// разрешается наследование дескрипторов
	};

	CreatePipe( // создание канала
		&hRead,	
		&hWrite,
		&sa,	
		0		// размер буфера
	);

	size_t messageCount = 100;
	LPCWSTR otherProcessArgs = calloc(messageCount, sizeof(WCHAR));
	swprintf(otherProcessArgs, messageCount * sizeof(WCHAR), L"%d %d %d", 1, hWrite, hRead);

	STARTUPINFO* sti = calloc(1, sizeof(STARTUPINFO));// начальная информация
	sti->cb = sizeof(STARTUPINFO); // контрольный байт
	PROCESS_INFORMATION* pi = calloc(1, sizeof(PROCESS_INFORMATION)); // выходная информация с дескрипторами

	if (!CreateProcess(// создание процесса
		otherProcessPath,//путь к файлу
		otherProcessArgs,//агрументы командной строки
		NULL,//структура безопасности процесса
		NULL,//структура безопасности потока
		TRUE,//наследовать дескриптор нового процесса от старого?
		0,//флаги приоритета процессов CREATE_NEW_CONSOLE
		NULL,//среда окружения процесса ANSI или UNICODE
		NULL,//консольный путь к каталогу, из которого вызывается процесс
		sti,//указатель на структуру STARTUPINFO
		pi))//указатель на структуру PROCESS_INFORMATION
	{
		wprintf(L"Ошибка создания процесса: %d\n", GetLastError());
		return -1;
	}
	wprintf(L"Процесс создан успешно\n");

	free(otherProcessArgs);
	CloseHandle(hRead);// закрываем дескриптор для чтения (сервер только пишет)

	int written;
	LPCWSTR message = L"Сообщение для благодарных потомков";
	WriteFile(hWrite, message, wcslen(message) * sizeof(WCHAR), &written, NULL); // запись в канал

	system("pause");

	message = L"сообщ2";
	WriteFile(hWrite, message, wcslen(message) * sizeof(WCHAR), &written, NULL);// запись в канал 2

	CloseHandle(hWrite); 
	WaitForSingleObject(pi->hProcess, INFINITE);//ожидание завершения дочернего процесса
	DWORD dw;
	GetExitCodeProcess(pi->hProcess, &dw);//получаем код выхода дочернего процесса
	CloseHandle(pi->hThread);
	CloseHandle(pi->hProcess);

	wprintf(L"Родитель дождался ребенка, который завершился с кодом %d\n", dw);

	return 0;
}