
// 26. Программа для считывания числового значения из файла (с сохранением его в числовом формате). 
// Исходный файл является бинарным 

// 1. Открытие на запись
// 2. Подготовка буфера и переменной для хранения кол-ва записанных байт
// 3. Запись и проверка
// 4. Открытие на чтение
// 5. Подготовка буфера и переменной для хранения кол-ва считанных байт
// 6. Чтение и проверка


#include "tasks.h"
#include <Windows.h>
#include <stdio.h>

HANDLE openFile(LPCSTR fileName, DWORD accessMode, DWORD creationMode) {
    return CreateFile(
        fileName,
        accessMode,
        0,
        NULL,
        creationMode,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
}


int _26_binaryFiles_Test() {
    system("chcp 1251>nul");
    LPCSTR fileName = L"data.bin";

    // Открытие файла для записи
    HANDLE hWrite = openFile(fileName, GENERIC_WRITE, CREATE_ALWAYS);
    if (hWrite == -1) {
        printf("Не удалось открыть файл для записи. Код ошибки: %lu\n", GetLastError());
        return -1;
    }

    int writtenNumber = 42, bytesWritten;
    if (!WriteFile(hWrite, &writtenNumber, sizeof(writtenNumber), &bytesWritten, NULL)) {
        printf("Ошибка при записи в файл. Код ошибки: %lu\n", GetLastError());
        CloseHandle(hWrite);
        return -1;
    }

    if (bytesWritten != sizeof(writtenNumber)) {
        printf("Записано недостаточно данных.\n");
        CloseHandle(hWrite);
        return -1;
    }

    printf("Число %d успешно записано в файл.\n", writtenNumber);
    CloseHandle(hWrite);

    // Открытие файла для чтения
    HANDLE hRead = openFile(fileName, GENERIC_READ, OPEN_EXISTING);

    if (hRead == INVALID_HANDLE_VALUE) {
        printf("Не удалось открыть файл для чтения. Код ошибки: %lu\n", GetLastError());
        return -1;
    }

    int readNumber = 0, bytesRead;
    if (!ReadFile(hRead, &readNumber, sizeof(readNumber), &bytesRead, NULL)) {
        printf("Ошибка при чтении файла. Код ошибки: %lu\n", GetLastError());
        CloseHandle(hRead);
        return -1;
    }

    if (bytesRead != sizeof(readNumber)) {
        printf("Файл содержит недостаточно данных.\n");
        CloseHandle(hRead);
        return -1;
    }

    printf("Считанное число: %d\n", readNumber);
    CloseHandle(hRead);

    return 0;
}