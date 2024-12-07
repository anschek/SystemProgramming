// Программа для преобразования строки в число. 
// Строка хранится в виде указателя LPWSTR. Реализовать без использования системных функций

// 1. знаем, что L'0'-0 и L'9'-9 дает одинаковое значение, а т.к. 0==0, исходная разность L'0'
// будем вычитать ее из символов, чтобы получить числа
// 2. определим цикл до тех пор, пока строка не закончилась (\0) или не началась дробная часть (.)
// 3. если оказалось, что дробная часть существует, считаем и ее
// 4. вернем сумму целой и дробной части


#include<Windows.h>
#include "tasks.h"
#include <stdio.h>


float LpwstrToNumber(LPWSTR str) {
	int integer_part = str[0] - L'0'; // целая часть числа
	int separator_index = 0; // дробная часть
	float fractional_part = 0; // знак разделения дробной и целой частей

	for (int i = 1; str[i] != L'\0' && str[i] != L'.'; ++i) { // пока не конец строки и не дробная часть
		integer_part = integer_part * 10 + str[i] - L'0';
		separator_index = i + 1;
	}
	if (str[separator_index] == L'.') { // если не конец строки, а конец целой части
		int cur_power = 10;
		for (int i = separator_index + 1; str[i] != L'\0'; ++i) {
			fractional_part += (str[i] - L'0')/ (float)cur_power;		
			cur_power *= 10;
		}
	}
	return integer_part + fractional_part;
}

int _9_lpwstrToNum_Test() {

	LPWSTR str = L"123";
	wprintf(L"%s - %d\n", str, (int)LpwstrToNumber(str));

	str = L"123.456";
	wprintf(L"%s - %.3f", str, LpwstrToNumber(str));

	return 0;
}