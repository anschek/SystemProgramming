#include <sys/stat.h>//mkfifo, S_I...
#include <fcntl.h>//O_...
#include <unistd.h>//read, write, open
#include <stdio.h>
#include <malloc.h>
#define PATH "/tmp/FIFOserver"
#define BUFFER_SIZE 256

int main(){
    //mkfifo(PATH, S_IRUSR| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    int counter = 0;
    while(1){
        char* inBuffer = calloc(BUFFER_SIZE, sizeof(char));
        char* outBuffer = calloc(BUFFER_SIZE, sizeof(char));

        int fifoWrite = open(PATH, O_WRONLY);
        int fifoRead = open(PATH, O_RDONLY);

        sprintf(outBuffer, "сообщение клиента %d", ++counter);
        write(fifoWrite, outBuffer, BUFFER_SIZE * sizeof(char) );
sleep(1);
        read(fifoRead, inBuffer,BUFFER_SIZE * sizeof(char) );
        printf("(клиент) получил ответ сервера: %s\n", inBuffer);

        close(fifoRead);
        close(fifoWrite);
    }
    return 0;
}