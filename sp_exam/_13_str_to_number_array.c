// ��������� ��� ���������� ���������� �������� �������� �� ������ � �� ������ � �������� ������ (����������� - ������). 
// ���������� �������� � ������ ������� ����������.

// 1. �������� ������� ����� ����� � ������������������ ������ �� ������
// 2. �������� ������� ����� ��� ������ �������
// 3. �� �������: ^z �� ����� ������ � ��������� �������, ���� ^q �� ���������


#include "tasks.h"
#include<stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include< string.h >


int* ReadToArray(int* size) {
	int array_size = 0;
	int* numbers = malloc(array_size * sizeof(int));
	int cur_number;
	while (scanf_s("%d", &cur_number)) {
		numbers = realloc(numbers, ++array_size * sizeof(int));
		numbers[array_size - 1] = cur_number;
	}
	getchar();
	getchar();
	*size = array_size;
	return numbers;
}

void PrintArray(int* array, int size) {
	for (int i = 0; i < size; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

int _13_strToArrayOfNumbers_Test() {
	int array_size;
	int* numbers = ReadToArray(&array_size);
	PrintArray(numbers, array_size);
	return 0;
}