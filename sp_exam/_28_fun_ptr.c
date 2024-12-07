// Создание функции, аргументом которой является указатель на функцию. 
// Создать не менее двух вспомогательных функций и передать их в качестве аргумента исходной функции. 
// Продемонстрировать специфику работы исходной функции в зависимости от переданных параметров 

// 1. создание функций с одной сигнатурой
// 2. переименование сигнатуры в отдельный тип
// 3. вызов функций в другой (с аргументами)

#include "tasks.h"

typedef int(*fun_i)(int, int);

int sum(int a, int b) {
	printf("     now used fun of sum\t");
	return a + b;
}
int divide(int a, int b) {
	printf("  now used fun of divide\t");
	return a - b;
}
int multiply(int a, int b) {
	printf("now used fun of multiply\t");
	return a * b;
}

void printFunResult(fun_i fun, int a, int b) {
	printf("args: %d %d\tresult: %d\n", a, b, fun(a, b));
}

int _28_funPtr_Test() {

	int a = 77, b = 23;
	fun_i funcs[] = {sum, divide, multiply};
	for (int i = 0; i < 3; ++i) printFunResult(funcs[i], a, b);

	return 0;
}