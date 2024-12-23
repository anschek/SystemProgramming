
// 11. Создание программы с критической секцией в ОС Windows. Программа должна содержать 
// минимум два потока. Использование критической секции в функции потока должно быть обосновано.

// 1. объявление критической секции, инициализация
// 2. объявление данных для потоков, в т.ч. подготовка вызываемых функций
// 3. создание потоков с использованием критической секции в функции, проверка на ошибки
// 4. определение результатов и высвобождение памяти


// *для примера можно закомментировать критическую секцию в функции и продемонстрировать,
// что счетчик будет меньше из-за состояния гонки

#include "tasks.h"
#include <stdio.h>
#include <Windows.h>
#include <malloc.h>

CRITICAL_SECTION cs;
int sharedCounter = 0;

DWORD WINAPI IncrementCounter(LPVOID param) {
	for (int i = 0; i < 100; ++i) {
		EnterCriticalSection(&cs);
		++sharedCounter; // Критическая секция защищает счетчик
		Sleep(1); // имитация деятельности
		LeaveCriticalSection(&cs);
	}
	return 0;
}


int _11_threads_Test() {
	system("chcp 1251>nul");

	int threadCount = 3;
	HANDLE* hThreads = calloc(threadCount, sizeof(HANDLE));
	
	InitializeCriticalSection(&cs);
	for (int i = 0; i < threadCount; ++i) {
		hThreads[i] = CreateThread(
			NULL, // структура безопасности
			0, // размер стека
			IncrementCounter, // указатель на функцию: LPTHREAD_START_ROUTINE
			NULL, // параметр функции, если есть: LPVOID
			0, // флаги создания
			NULL // id потока
		);

		if (!hThreads[i]) {
			printf("Ошибка создания потока %d. Код ошибки: %lu\n", i, GetLastError());
		}
	}

	// ожидаем завершение потоков
	WaitForMultipleObjects(threadCount, hThreads, TRUE, INFINITE);
	printf("Значение счетчика после завершения потоков: %d\n", sharedCounter);

	// Освобождаем ресурсы
	DeleteCriticalSection(&cs);
	for (int i = 0; i < threadCount; ++i) {
		CloseHandle(hThreads[i]);
	}
	free(hThreads);

	return 0;
}