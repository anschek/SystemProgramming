
// 26. Программа для считывания числового значения из файла 
// (с сохранением его в числовом формате). Исходный файл является бинарным

// то же самое, что и задание 5, только буфер - число

#include "tasks.h"
#include<stdio.h>
#include <sys/stat.h> //содержатся флаги режимов доступа к файлам (mode)
#include <fcntl.h> //содержатся флаги открытия файлов (flags)
#include <errno.h>
#include <unistd.h> // для чтения и записи
#include<malloc.h>
#include <string.h>


int OpenWithFlags(char* path, int flags){
    int hFile = open(path, flags, S_IRWXU|S_IRGRP|S_IROTH);
    if(hFile == -1){
        printf("ошибка открытия файла: %d\n", errno);
        _exit(errno);
    }
    return hFile;
}

void WriteIntByHandle(int hFile, int* buffer){
    int writtenBytes = write(hFile, buffer, sizeof(int));
    if(writtenBytes == -1){
        printf("ошибка записи в файл: %d\n", errno);
        _exit(errno); 
    }
    printf("записано байт: %d\n", writtenBytes);
}

int ReadIntByHandle(int hFile){
    int buffer;
    int readBytes = read(hFile, &buffer, sizeof(int));
    if(readBytes == -1){
        printf("ошибка чтения файла: %d\n", errno);
        _exit(errno);
    }
    if(readBytes != sizeof(int)){
        printf("считано: %d байт, ожидаемо: %d", readBytes, sizeof(int));
        _exit(-1);
    }
    printf("прочитано байт: %d\n", readBytes);
    return buffer;
}

int _26_binaryFiles_Test(){
    char* filePath = "./data.bin";

    int hWriteFile = OpenWithFlags(filePath, O_WRONLY|O_CREAT);
    int written = 100500;
    WriteIntByHandle(hWriteFile, &written);
    close(hWriteFile);

    int hReadFile = OpenWithFlags(filePath, O_RDONLY);
    int read = ReadIntByHandle(hReadFile);
    close(hReadFile);

    printf("%d\n", read);
    return 0;
}