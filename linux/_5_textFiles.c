
// 5. Программа для считывания и записи строкового значения из текстового файла 
// с последующей записью его в другой текстовый файл.

// 1. функция открытия с флагами
// 2. функция чтения
// 3. функция записи
// 4. закрытие дескрипторов и освобождение памяти

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

char* ReadByHandle(int hFile){
    char* buffer = calloc(100, sizeof(char));
    int readBytes = read(hFile, buffer, 100);
    if(readBytes == -1){
        printf("ошибка чтения файла: %d\n", errno);
        _exit(errno);
    }
    printf("прочитано %d байт: %s\n", readBytes, buffer);
    return buffer;
}

void WriteByHandle(int hFile, char* buffer){
    int writtenBytes = write(hFile, buffer, strlen(buffer)*sizeof(char));
    if(writtenBytes == -1){
        printf("ошибка записи в файл: %d\n", errno);
        _exit(errno); 
    }
    printf("записано байт: %d", writtenBytes);
}

int main(){

    int hReadFile = OpenWithFlags("./input.txt", O_RDONLY);
    char* buffer = ReadByHandle(hReadFile);
    close(hReadFile);

    int hWriteFile = OpenWithFlags("./output.txt", O_WRONLY|O_CREAT);
    WriteByHandle(hWriteFile, buffer);
    close(hWriteFile);
    free(buffer);

    return 0;
}