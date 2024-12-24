
// 12. Создание программы с критической секцией в ОС Linux. Программа 
// должна содержать минимум два потока. Использование критической секции 
// в функции потока должно быть обосновано.

// 1. объявление мьютекса и функции потока
// 2. создание потоков
// 3. присоединение и возврат результатов

// компиляция с флагом -pthread

#include "tasks.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <time.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int counter=0;

static void* threadFunc(void *arg)
{  
    for (size_t i = 0; i < *(int*)arg; ++i)
    {
        pthread_mutex_lock(&mtx);
        counter+=1000;
        printf("%d\n", counter);
        sleep(1);
        pthread_mutex_unlock(&mtx);
    }   
}

int _12_threads_Test()
{
    int threadCount = 3;
    pthread_t* t = calloc(threadCount, sizeof(pthread_t));
    pthread_t t1,t2,t3;

    int n = 10;//количество итераций в цикле
    for(int i=0; i<threadCount; ++i){
        pthread_create(&t[i], NULL, threadFunc, &n);
    }  

    for(int i=0; i<threadCount; ++i){
        pthread_join(t[i], NULL);
    }

    printf("Результат инкрементации: %d\n",counter); //теперь counter = n*3
    return 0;
}