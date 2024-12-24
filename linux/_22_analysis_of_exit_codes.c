
// 22. Использование условных блоков для анализа значений, возвращаемых системной функцией 

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include<sys/wait.h>
#include<string.h>

void open_Test(char* path, int flags) {
    int hFile = open(path, flags);
    if (hFile == -1) {
        printf("Ошибка открытия файла: %s\n", strerror(errno));
    } else {
        printf("Файл успешно открыт: дескриптор = %d\n", hFile);
        close(hFile);
    }
}

void fork_Test() {
    pid_t pid = fork();
    if (pid == -1) {
        printf("Ошибка вызова fork");
    } else if (pid == 0) {
        printf("Дочерний процесс (PID = %d)\n", getpid());
        exit(0);
    } else {
        printf("Родительский процесс (PID = %d, дочерний PID = %d)\n", getpid(), pid);
        wait(NULL);
    }
}

void write_Tests(int hFile) {
    const char* text = "Hello, world!";
    ssize_t result;
    result = write(hFile, text, 13);
    if (result >= 0) {
        printf("Успешно записано %zd байт\n", result);
    } else {
        printf("Ошибка записи: %s\n", strerror(errno));
    }
}

int _22_analysisOfExitCodes_Test(){
    printf("--open--\n");
    open_Test("./new_file", O_RDWR|O_CREAT);
    open_Test("./not_existing_file", O_RDWR);

    printf("--fork--\n");
    fork_Test();

    printf("--write--\n");

    int hFile = open("output.txt", O_WRONLY | O_CREAT, 0644);
    write_Tests(hFile);
    close(hFile);
    write_Tests(hFile);

    return 0;
}
