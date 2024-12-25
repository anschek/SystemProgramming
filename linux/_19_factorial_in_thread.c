
// 19. Разработка программы для вычисления факториала в отдельном потоке. 
// В программе должна быть предусмотрена валидация данных 

// 1. создание функции вычисление факториала
// 2. считывание данных и их валидация
// 3. создание потока 
// 4. присоединение и получения результата

#include<stdio.h>
#include <pthread.h>
#include <unistd.h>

void* CalcFactorial(void* param)
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
    pthread_exit(f);
}

int _19_calcFactorialInSingleThread_Test(){
    int n = 0;
    printf("Введите число: ");
    if (!scanf("%d", &n) || n<0) {
        printf("Значение должно быть целым неотрицательным числом\n");
        return -1;
    }
    pthread_t hThread;
    pthread_create(&hThread, NULL, CalcFactorial, &n);
    int* result;
    pthread_join(hThread, &result);
    close(hThread);
    printf("Факториал числа %d равен %d\n", n, result);
    return 0;
}
