
// 21. Программа с запуском стороннего процесса исполняемый файл 
// стороннего процесса подготавливается заранее 

// 1. объявление id дочернего процесса и аргументов запуска
// 2. fork и опредение части программ каждому процессц
// 3. ожидание завершения дочернего процесса, получение кода возврата

#include "tasks.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int _21_processes_Test(){
    __pid_t externProcessId;
    char* externArgv[] = {"aala", "первый", "второй", "третий"}; //аргументы командной строки дочернего процесса
    char* externEnvp[] = {NULL}; //окружение дочернего процесса
    switch(externProcessId=fork()){
        case -1:
        printf("ошибка создания процесса\n");
        exit(-1);
        break;

        case 0:
        printf("код дочернего процесса\n");
        execve("extern_process", externArgv, externEnvp);
        printf("дочерний процесс не создался, ошибка: %d\n", errno);
        break;

        default:
        printf("код родительского процесса\n");
        break;
    }

    int status;
    waitpid(externProcessId, &status, NULL);
    printf("Дочерний процесс с id=%d завершился с кодом %d\n", externProcessId, WEXITSTATUS(status));
    return 0; 
}