#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

int main (void) {

	Listptr list1, list2, list3;
	long curtime = time(NULL);
	int i;

	srand(curtime);

	// Create and print first list
	Create(&list1);
	for (i = 0; i < LIST_SIZE; i++) {
		InsertAtStart(&list1);
	}
	printf("\nList 1:\n");
	PrintList(list1);
	
	// Create and print second list
	Create(&list2);
	for (i = 0; i < LIST_SIZE; i++) {
		InsertAtStart(&list2);
	}
	printf("\nList 2:\n");
	PrintList(list2);
	
	// Print sorted list1
	SortList(&list1);
	printf("\nSorted List 1:\n");
	PrintList(list1);
	
	//Print sorted list2
	SortList(&list2);
	printf("\nSorted List 2:\n");
	PrintList(list2);
	
	// Create and print new sorted list3
	list3 = Sort2Lists(&list1, &list2);
	printf("\nSorted List 3:\n");
	PrintList(list3);
	
	FreeList(&list3);

	return 0;
}
