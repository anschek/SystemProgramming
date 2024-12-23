
// 18. Разработка программы-секундомера. в одном потоке идет отсчет времени, 
// а в другом осуществляется управление секундомером 

// 1. Определние переменных и функции для основной работы
// 2. Создание функции управления с основными десйтвиями:
//      - вывод
//      - пауза SuspendThread
//      - снятие с паузы ResumeThread
//      - прерывание TerminateThread
// 3. Создание потоков в основной функции
// 4. Ожидание, очитска данных

#include "tasks.h"
#include <Windows.h>
#include <stdio.h>
#include <malloc.h>

HANDLE hThreads[2];
int seconds = 0;
char* buffer;

// поток, к-й ведет отчет времени
DWORD WINAPI TreadWorker(LPVOID param)
{
    while (TRUE)
    {
        Sleep(1000); // 1000ms == 1s
        seconds++;
    }
}

// поток управления секундомером
DWORD WINAPI TreadManager(LPVOID param)
{
    int option;
    buffer = calloc(10, sizeof(char));
    while (TRUE)
    {
        // выбор действия пользователя
        printf("Выберите действие:\n1-значение секундомера\n2-пауза\n3-снять с паузы\n4-завершить работу\n");
        scanf_s("%d", &option);
        // определние времени
        memset(buffer, 0, 10 * sizeof(char)); // зануление строки
        sprintf_s(buffer, 10, "%02d:%02d", seconds / 60, seconds % 60); // получение времени в формате 00:00
        // десйтвие
        switch (option)
        {
        case 1:
            printf("Значение счетчика %s\n",buffer);
            break;

        case 2:
            printf("Рабочий поток поставлен на паузу на значении %s\n", buffer);
            SuspendThread(hThreads[0]);
            break;

        case 3:
            printf("Рабочий поток снят с паузы\n");
            ResumeThread(hThreads[0]);
            break;

        case 4:
            printf("Все потоки завершили работу, последнее время таймера %s\n", buffer);
            TerminateThread(hThreads[0], 0);
            ExitThread(0);
            break;

        default:
            printf("Ничего не изменилось\n");
            break;

        }
    }
}



int _18_threadingStopwatch_Test() {
    system("chcp 1251");

    hThreads[0] = CreateThread(NULL, 0, TreadWorker, NULL, 0, 0); // запуск рабочей функции
    hThreads[1] = CreateThread(NULL, 0, TreadManager, NULL, 0, 0);// запуск потока управления

    WaitForMultipleObjects(2, hThreads, TRUE, INFINITE); 
    free(buffer);
    CloseHandle(hThreads[0]);
    CloseHandle(hThreads[1]);

    return 0;
}