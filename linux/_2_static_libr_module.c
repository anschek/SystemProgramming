#include "_2_static_libr_module.h"
#include<stdio.h>
#include<math.h>

extern void fun1(char* str){
    printf("1ая функция статической библиотеки выводит: %s\n", str);
}

extern int fun2(int a, int b){
    return pow(a, b);
}