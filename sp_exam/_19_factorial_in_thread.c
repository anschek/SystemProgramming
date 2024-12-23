
// 19. Разработка программы для вычисления факториала в отдельном потоке.
// В программе должна быть предусмотрена валидация данных

#include "tasks.h"
#include <Windows.h>
#include <stdio.h>

DWORD WINAPI CalcFactorial(LPVOID param)
{
    printf("поток начал работу\n");
    int n = *(int*)param;
    int f = 0;
    for (int i = 0; i <= n; i++)
    {
        if (i == 0) f = 1;
        else f *= i;
    } 
    printf("поток завершил работу\n");
    ExitThread(f);
}


int _19_factorialInSingleThread_Test() {
    system("chcp 1251>nul");
    int n = 0;
    printf("Введите число: ");
    if (!scanf_s("%d", &n) || n<0) {
        printf("Значение должно быть целым неотрицательным числом\n");
        return -1;
    }
    HANDLE hThread = CreateThread(NULL, 0, CalcFactorial, &n, 0, 0);
    WaitForSingleObject(hThread, INFINITE);

    int result;
    GetExitCodeThread(hThread, &result);

    CloseHandle(hThread);
    printf("Факториал числа %d равен %d\n", n, result);

    return 0;
}