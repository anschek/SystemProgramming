
// 18. Разработка программы-секундомера. в одном потоке идет отсчет времени,  
// а в другом осуществляется управление секундомером 

// 1. создание рабочего потока
// 2. создание обработчика сигнала для паузы
// 3. создание менеджера с 4 функциями
// 4. инициализация потоков и их присоединение

#include "tasks.h"
#include<pthread.h>
#include<stdio.h>
#include<signal.h>

//int count = 0;
int seconds = 0;
pthread_t workerThread, managerThread;

void signalHandler(int signum) {
    if (signum == SIGUSR1) {
        pause(); // останавливает поток до тех пор, пока он не получит любой сигнал, для которого есть обработчик
    }
    // else if (signum == SIGUSR2)
    // по факту если значение не равно SIGUSR1, возобновляется деятельность
}

void* WorkerThread(void* param){
    signal(SIGUSR1, signalHandler);
    signal(SIGUSR2, signalHandler); // если не определить, будет ошибка не обработанного пользовательского сигнала

    while(1){
        sleep(1);
        ++seconds;  
    }
    pthread_exit(NULL);
}

void* ManagerThread(void* param){
    int option;
    char buffer[12];

    while(1){
        printf("Выберите действие:\n1 - Значение секундомера\n2 - Пауза\n3 - Снять с паузы\n4 - Завершить работу\n");
        scanf("%d", &option);
        sprintf(buffer, "%02d:%02d", seconds/60, seconds%60);

        switch (option)
        {
        case 1: // просмотр
            printf("Значение счетчика: %s\n", buffer);
            break;
        case 2: // пауза
            printf("Рабочий поток приостанавливается на значении: %s\n", buffer);
            pthread_kill(workerThread, SIGUSR1);
            break;
        case 3: // возобновление
            printf("Рабочий поток возобновляется\n");
            pthread_kill(workerThread, SIGUSR2);
            break;
        case 4: // заверешние работы
            printf("Завершаем все потоки, последнее значение таймера: %s\n", buffer);
            pthread_cancel(workerThread); // Завершение рабочего потока
            pthread_join(workerThread, NULL);
            pthread_exit(NULL);
            break;
        default:
        printf("нет такого действия\n");
            break;
        }
    }
    pthread_exit(NULL);
}

int _18_threadingStopwatch_Test(){

    pthread_create(&workerThread, NULL, WorkerThread, NULL);
    pthread_create(&managerThread, NULL, ManagerThread, NULL);
   
    pthread_join(managerThread, NULL); 

    printf("потоки освобождены\n");
    return 0;
}