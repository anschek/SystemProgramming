
// 3. Создание динамической библиотеки в Linux. Для демонстрации работы 
// написать две элементарные функции в библиотеке и вызвать их из 
//основной программы.

// 1. cсоздание модуля библиотеки и компиляция
// gcc -fPIC _2_static_libr_module.c -shared -o dynamic_lib.so -lm

// 2. определение указателей на функцию
// 3. открытие библиотеки
// 4. вызов
// 5. закрытие

// 6. общая компиляция
// gcc -o program main.c _3_dynamic_lib.c -ldl

#include "tasks.h"
#include "_2_static_libr_module.h"
#include <dlfcn.h>
#include <stdio.h>

typedef void(*fun1Dll)(char*);
typedef int(*fun2Dll)(int,int);

int _3_dynamicLibrary_Test(){
    void* hDll = dlopen("./dynamic_lib.so", RTLD_LAZY);
    fun1Dll fun1 = dlsym(hDll, "fun1");
    fun2Dll fun2 = dlsym(hDll, "fun2");

    fun1("str from task 3");
    printf("2^3=%d\n", fun2(2,3));

    dlclose(hDll);
    return 0;
}