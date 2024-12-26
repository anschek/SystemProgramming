
// 29. Использование анонимного канала для передачи строковых значений между процессами

//1. Создание канала и нового процесса
//2. Выполнение чтения на стороне клиента по входному дескриптору канала
//3. Выполнение записи на стороне сервера по выходному дескриптору канала
//4. Ожидание заверешения ребенка и закрытие дескрипторов

#include "tasks.h"
#include <stdio.h>
#include <unistd.h> //fork, close, read, write, pipe, _exit
#include <sys/wait.h> //wait
#include <string.h>//strlen
#include <malloc.h>
#include <errno.h>

#define BUFFER_SIZE 256
#define MESSAGE_COUNT 3

int Client(int hReadPipe, int hWritePipe){
    if (close(hWritePipe) == -1) // Записывающий конец не используется
        _exit(1);
    int numRead = 0;
    do
    { // Считываем данные из канала до тех пор, пока он не опустеет
        char* inBuffer = calloc(BUFFER_SIZE, sizeof(char));//создаем буфер для чтения
        numRead = read(hReadPipe, inBuffer, BUFFER_SIZE);//операция блокируется до тех пор, пока в канал не поступят данные
        if (numRead == -1)
            _exit(-1);  

        printf("(клиент) прочел %d байт сообщение: %s\n", numRead, inBuffer);//выводим на экран то, что прочитали
        free(inBuffer);//очищаем буфер

    }while (numRead != 0); 

    if (close(hReadPipe) == -1)
        _exit(-1);

    return 0;
}

int Server(int hReadPipe, int hWritePipe){
    if (close(hReadPipe) == -1) // Считывающий конец не используется
        _exit(-1);
    
    for(int i=0; i<MESSAGE_COUNT; ++i){
        char *outBuffer = calloc(BUFFER_SIZE, sizeof(char));
        sprintf(outBuffer, "Сообщение № %d", i);

        if (write(hWritePipe, outBuffer, (strlen(outBuffer))*sizeof(char) ) == -1)
            _exit(-1);

        free(outBuffer);
        sleep(1);
    }

    if (close(hWritePipe) == -1) // Потомок увидит символ завершения файла
        _exit(1);

    wait(NULL); // Ждем завершения потомка
    return 0;
}

int _29_unnamedPipe_Tests(){
    int hPipe[2]; // 0- r, 1 - w

    if (pipe(hPipe) == -1){ // Создаем канал
    printf("Ошибка создания канала: %s", strerror(errno));
    _exit(-1);
    }

    switch (fork()) {
    case -1:
        printf("Ошибка создания процесса: %s", strerror(errno));
        _exit(1);

    case 0: //потомок только читает данные из канала
        Client(hPipe[0], hPipe[1]);

    default: // Родитель записывает в канал
        Server(hPipe[0], hPipe[1]);
    }
}