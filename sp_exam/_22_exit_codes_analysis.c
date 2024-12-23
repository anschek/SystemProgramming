 
// 22. Использование условных блоков для анализа значений, 
// возвращаемых системной функцией (не менее трех функций)

// 1. Открытие ключа реестра: ERROR_SUCCESS, ERROR_FILE_NOT_FOUND
// 2. Открытие файла: не -1 успех, если -1: ERROR_FILE_NOT_FOUND, ERROR_ACCESS_DENIED
// 3. Ожидание потока: WAIT_OBJECT_0, WAIT_TIMEOUT

// * все ошибки определены в winerror.h

#include "tasks.h"
#include <Windows.h>
#include <stdio.h>

void RegOpenKey_Test(LPCWSTR subKeyName) {
    HKEY hKey;
    LSTATUS status;

    status = RegOpenKey(HKEY_CURRENT_USER, subKeyName, &hKey);
    printf("%d: ", status);
    if (status == ERROR_SUCCESS) {// Ключ существует
        printf("Ключ открыт успешно\n");
        RegCloseKey(hKey);
    }
    else if (status == ERROR_FILE_NOT_FOUND) {// Ключ не существует
        printf("Ключ не найден\n");
    }
    else {
        printf("Ошибка открытия ключа: %ld\n", status);
    }  
}

void CreateFile_Test(LPCWSTR filePath) {
    HANDLE hFile;

    hFile = CreateFile(
        filePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) { // значение не -1
        printf("Файл открыт успешно\n");
        CloseHandle(hFile);
    }
    else {// значение -1
        DWORD error = GetLastError();
        printf("%d: ", error);
        if (error == ERROR_FILE_NOT_FOUND) {
            printf("Файл не найден\n");
        }
        else if (error == ERROR_ACCESS_DENIED) {
            printf("Доступ запрещен\n");
        }
        else {
            printf("Ошибка открытия файла: %ld\n", error);
        }
    }
}

DWORD WINAPI ThreadFunction(LPVOID param) {
    Sleep(300); // Имитация работы потока
    return 0;
}

void ThreadWait_Test(DWORD milliseconds) {
    HANDLE hThread = CreateThread(
        NULL,      // атрибуты безопасности
        0,         // размер стека
        ThreadFunction, // функция потока
        NULL,      // параметр для функции
        0,         // флаги создания
        NULL       // идентификатор потока
    );


    DWORD waitResult = WaitForSingleObject(hThread, milliseconds);
    printf("%d: ", waitResult);
    if (waitResult == WAIT_OBJECT_0) {// Поток завершился вовремя
        printf("Поток завершился успешно\n");
    }
    else if (waitResult == WAIT_TIMEOUT) {// Время истекло
        printf("Ожидание завершения потока истекло (таймаут)\n");
    }
    else {
        printf("Ошибка ожидания завершения потока: %lu\n", GetLastError());
    }

    CloseHandle(hThread);
}

int _22_analysisOfExitCodes_Test() {
    system("chcp 1251>nul");
    printf("--Сценарии открытия ключа регистра--\n");
    RegOpenKey_Test(L"SOFTWARE");
    RegOpenKey_Test(L"SOFTWARE\\NonExistentKey");    
    
    printf("--Сценарии открытия файла--\n");
    CreateFile_Test(L"log.txt");
    CreateFile_Test(L"0.txt");
    CreateFile_Test(L"C:\\Windows\\System32\\config\\SAM");

    printf("--Сценарии ожидания заверешения потоков--\n");
    ThreadWait_Test(500);
    ThreadWait_Test(100);
    return 0;
}