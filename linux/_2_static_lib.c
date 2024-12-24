
// 2. Создание статической библиотеки в Linux. Для демонстрации работы написать 
// две элементарные функции в библиотеке и скомпилировать библиотеку вместе с 
// основной программой

// 1. создание кода библиотеки и заголвочного файла
// 2. использование функций заголовочного файла в основной программе
// 3. компиляция:

// gcc -c _2_static_libr_module.c -o module.o
// ar rc static_lib.a module.o
// ranlib static_lib.a
// gcc main.c _2_static_lib.c static_lib.a -o program -lm

// объектный модуль -> библиотека -> индексация -> связь файлов

#include "tasks.h"
#include"_2_static_libr_module.h"

int _2_staticLibrary_Test(){
    
    fun1("string from task 2");
    printf("fun2 2^7=%d", fun2(2,7));
    return 0;
}