
// 30. создание фонового процесса, который каждые 5 секунд выводит всплывающее 
// или диалоговое сообщение, содержащее увеличивающееся на единицу значение счетчика 

// 1. настройка компоновщик/все параметры/подсистема/win
// 2. определение сигнатуры метода winmain
// 2. тело программы

// * для закрытия программы taskkill /IM process.exe /F

#include <Windows.h>
#include <stdio.h>

#define TIMER_INTERVAL 5000 // 5 секунд

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
) {
    int counter = 0;
    int clicked = IDOK;
    do{
        LPCWSTR message = calloc(1000, sizeof(WCHAR));
        swprintf_s(message, 1000, L"%d", counter);
        clicked = MessageBox(NULL, message, L"Счетчик", MB_OKCANCEL);
        ++counter;
        Sleep(5000);
    } while (clicked != IDCANCEL);
    return 0;
}