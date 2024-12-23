
// 8. Программа для преобразования числа в строку и склейки двух строк. 
// Разработать без использования системных функций

// Для числа в строку:
// 1. Определение знака, выделение буфера, нормализация исходного числа
// 2. Цикл с записью строки и уменьшением числа
// 3. Добавление знака и переворот строки
// 4. Очистка исходного буфера

// Для конкатенации:
// 1. Определение длины нового слова, буфера и итератора
// 2. Посимвольный цикл со сменой итератора

#include "tasks.h"
#include <stdio.h>
#include <malloc.h>

char* IntToString(int num) {
	char isNegative = num < 0 ? 1 : 0; // число отрицательно?
	int bufferCount = 1; // текущая длина строки под \0
	char* buffer = calloc(bufferCount,sizeof(char)); // хранилище строки
	if (isNegative) num = -num; 

	do {
		++bufferCount;
		buffer = realloc(buffer, bufferCount*sizeof(char)); // перераспределеяем буфер
		buffer[bufferCount - 2] = (num % 10) + '0'; // записываем символы
		num /= 10; // убираем последний разряд
		printf("str: %s, new num: %d\n", buffer, num);
		
	} while (num > 0);

	if (isNegative) {
		++bufferCount;
		buffer = realloc(buffer, bufferCount * sizeof(char));
		buffer[bufferCount - 2] ='-';
	}

	// исходную строку надо развернуть
	char* stringNum = calloc(bufferCount, sizeof(char)); 
	for (int i = 0; i < bufferCount-1; ++i) {
		stringNum[i] = buffer[bufferCount - 2 - i];
	}

	free(buffer);
	return stringNum;
}

char* Concat(char* str1, char* str2) {
	int bufferCount = strlen(str1) + strlen(str2) + 1; // длина 2 строк + \0
	char* buffer = calloc(bufferCount, sizeof(char));
	char* iterator = str1; // итератор на текущую позицию
	for (int i = 0; i < bufferCount - 1; ++i) { // цикл до \0
		// если первое слово закончено, переход к второму
		if (i == strlen(str1)) iterator = str2; 
		buffer[i] = *iterator;
		++iterator;
	}
	return buffer;
}

int _8_numToStringAndConcat_Test() {
	// тесты для разных чисел
	printf("1234567890 == %s\n", IntToString(1234567890));
	printf("-1234567890 == %s\n", IntToString(-1234567890));
	printf("1 == %s\n", IntToString(1));
	printf("21 == %s\n", IntToString(21));
	printf("0 == %s\n", IntToString(0));


	// тесты для конкатенации
	printf("123+hsgd=%s\n", Concat("123", "hsgd"));
	printf("cat+Dog0=%s\n", Concat("cat", "Dog0"));
	return 0;
}