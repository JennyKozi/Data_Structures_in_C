#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct node {
	ListItem data;
	struct node *next;
} ListNode;

void Create(Listptr *list) {
	(*list) = NULL;
}

int IsEmpty(Listptr list) {
	return(list == NULL);
}

void InsertAtStart(Listptr *list) {
	Listptr newnode, current;
	current = *list;

	newnode = malloc(sizeof(struct node));
	if (newnode == NULL) {
		printf("Cannot allocate memory!\n");
		exit(1);
	}
	newnode->data = rand() % 1000;
	newnode->next = current;
	*list = newnode;
}

void PrintList(Listptr list) {
	Listptr current = list;
	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

void FreeList(Listptr *list) {
	Listptr temp;
	while ((*list) != NULL) {
		temp = (*list)->next;
		free(*list);
		*list = temp;
	}
}

// Use this function to sort one list
void SortList(Listptr *list) {
	Listptr temp, current, sorted = NULL;
	current = *list;
	while (current != NULL) {
		temp = current->next;
		InsertSort(&sorted, current);
		current = temp;
	}
	*list = sorted;
}

void InsertSort(Listptr *list, Listptr node) {
	Listptr current;
	if (*list == NULL || (*list)->data > node->data) {
		node->next = *list;
		*list = node;
	}
	else {
		current = *list;
		while (current->next != NULL) {
			if (node->data < current->next->data) {
				node->next = current->next;
				current->next = node;
				return;
			}
			current = current->next;
		}
		node->next = current->next;
		current->next = node;
	}
}

// Use this function to sort two lists
// Since list1 and list2 are sorted, list1 is used as the new sorted list and by using the function InsertSort,
//each node of list2 is placed correctly to the sorted list1
Listptr Sort2Lists(Listptr *list1, Listptr *list2) {
	Listptr temp, current, sorted;
	current = *list2;
	sorted = *list1;
	while (current!=NULL) {
		temp = current->next;
		InsertSort(&sorted, current);
		current = temp;
	}
	return sorted; // Return pointer to a new sorted list
}
