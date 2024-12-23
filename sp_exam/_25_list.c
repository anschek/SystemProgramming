
// 25.Создание линейного односвязного списка из n элементов. Значение элемента генерируется случайным образом. 
// Поместить в отдельные указатели адрес минимального и максимального элемента списка. 
// Вывести список и значения минимального и максимального элемента через указатель

// 1. Определить структуру спсика и ее поля
// 2. Создать функцию инициализации списка
// 3. Создать функцию вывода списка
// 4. Создать функцию поиска экстремумов

#include "tasks.h"
#include <stdio.h>
#include <malloc.h>
// для рандома
#include <time.h>
#include <stdlib.h>

struct List;
typedef struct List List;

struct List {
	int index;
	int value;
	List* next;
};

List* InitList(int n, int min, int max) {
	srand(time(NULL));
	List *start_elem, *cur_elem, *next_elem;
	start_elem = calloc(1, sizeof(List));
	start_elem->index = 0;
	start_elem->value = rand() % (max-min) + min;
	cur_elem = start_elem;
	for (int i = 1; i < n; ++i) {
		next_elem = calloc(1, sizeof(List));
		next_elem->index = i;
		next_elem->value = rand() % (max-min) + min;

		cur_elem->next = next_elem;
		cur_elem = next_elem;
	}
	return start_elem;
}

void PrintList(List* list) {
	List* cur_elem = list;
	while (cur_elem) {
		printf("list[%d]=%d\n", cur_elem->index, cur_elem->value);
		cur_elem = cur_elem->next;
	}
}

void FindExtremes(List* list, List** min_elem, List** max_elem) {
	List* cur_elem = list;
	*min_elem = list; *max_elem = list;
	cur_elem = cur_elem->next;
	while (cur_elem) {
		int cur_value = cur_elem->value;
		if (cur_value > (*max_elem)->value) *max_elem = cur_elem;
		if (cur_value < (*min_elem)->value) *min_elem = cur_elem;
		cur_elem = cur_elem->next;
	}
}

int _25_list_Test() {
	int n = 10, min = -50, max = 51;
	List* list = InitList(n, min, max);
	PrintList(list);

	List* list_max = NULL, *list_min = NULL;
	FindExtremes(list, &list_min, &list_max);
	printf("\nmax: list[%d]=%d\tmin: list[%d]=%d\n", list_max->index, list_max->value, list_min->index, list_min->value);
	return 0;
}