#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

// Insertion sort

int main(void) {

	Listptr list;
	long curtime = time(NULL);
	int i, size;

	printf("\nInsert number of nodes for the list: ");
	scanf("%d", &size);
	if (size < 1) {
		printf("\nWrong Input!\n");
	}

	srand(curtime);
	Create(&list);
	
	for (i = 0; i < size; i++) {
		InsertAtStart(&list);
	}
	printf("\nList:\n");
	PrintList(list);
	SortList(&list);
	printf("\nSorted List:\n");
	PrintList(list);
	FreeList(&list);

	return 0;
}
