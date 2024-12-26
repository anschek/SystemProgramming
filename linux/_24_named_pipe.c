
// 24. Отправка и получение данных из именованного канала. 
// Данные содержатся в строковой форме. Перед отправкой 
// следующей строки клиенту необходимо дождаться ответа от сервера 

// на сервере
// 1. создание и открытие очереди
// 2. чтение сообщений клиента, отправка ответов

// на клиенте
// 3. открытие очереди по сетевому имени
// 4. отправка сообщений серверу
// 5. принятие ответов

#include "tasks.h"
#include <sys/stat.h>//mkfifo, S_I...
#include <fcntl.h>//O_...
#include <unistd.h>//read, write, open
#include <stdio.h>
#include <malloc.h>
#define PATH "/tmp/FIFOserver"
#define BUFFER_SIZE 256

int _24_namedPipe_Test(){
    mkfifo(PATH, S_IRUSR| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    int counter = 0;
    while(1){
        char* outBuffer = calloc(BUFFER_SIZE, sizeof(char));
        char* inBuffer = calloc(BUFFER_SIZE, sizeof(char));

        int fifoRead = open(PATH, O_RDONLY|O_NONBLOCK);
        int fifoWrite = open(PATH, O_WRONLY|O_NONBLOCK);

        if (read(fifoRead, inBuffer,BUFFER_SIZE * sizeof(char) ) > 0){
            printf("(сервер) получил сообщение от клиента: %s\n", inBuffer);

            sprintf(outBuffer, "OK %d", ++counter);
            write(fifoWrite, outBuffer, BUFFER_SIZE * sizeof(char) );
        }else{
            printf("(сервер) работает, сообщений нет\n");
        }
        sleep(1);

        close(fifoRead);
        close(fifoWrite);
    }
    return 0;
}