// ��������� ��� �������������� ������ � �����. 
// ������ �������� � ���� ��������� LPWSTR. ����������� ��� ������������� ��������� �������

// 1. �����, ��� L'0'-0 � L'9'-9 ���� ���������� ��������, � �.�. 0==0, �������� �������� L'0'
// ����� �������� �� �� ��������, ����� �������� �����
// 2. ��������� ���� �� ��� ���, ���� ������ �� ����������� (\0) ��� �� �������� ������� ����� (.)
// 3. ���� ���������, ��� ������� ����� ����������, ������� � ��
// 4. ������ ����� ����� � ������� �����


#include<Windows.h>
#include "tasks.h"
#include <stdio.h>


float LpwstrToNumber(LPWSTR str) {
	int integer_part = str[0] - L'0'; // ����� ����� �����
	int separator_index = 0; // ������� �����
	float fractional_part = 0; // ���� ���������� ������� � ����� ������

	for (int i = 1; str[i] != L'\0' && str[i] != L'.'; ++i) { // ���� �� ����� ������ � �� ������� �����
		integer_part = integer_part * 10 + str[i] - L'0';
		separator_index = i + 1;
	}
	if (str[separator_index] == L'.') { // ���� �� ����� ������, � ����� ����� �����
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