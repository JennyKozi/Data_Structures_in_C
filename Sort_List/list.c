#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct node {
	ListItem data;
	struct node *next;
} ListNode;

// Create a new list
void Create(Listptr *list) {
	(*list) = NULL;
}

// Check if the list is empty
int IsEmpty(Listptr list) {
	return(list == NULL);
}

// Insert a new node at start
void InsertAtStart(Listptr *list) {
	Listptr newnode, current;
	current = *list;

	newnode = malloc(sizeof(struct node));
	if (newnode == NULL) {
		printf("Cannot allocate memory!\n");
		exit(1);
	}
	newnode->data = rand() % 1000; // The list is created by random numbers
	newnode->next = current;
	*list = newnode;
}

// Print list
void PrintList(Listptr list) {
	Listptr current = list;
	while (current!=NULL) {
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

// Free memory
void FreeList(Listptr *list) {
	Listptr temp;
	while ((*list) != NULL) {
		temp = (*list)->next;
		free(*list);
		*list = temp;
	}
}

void SortList(Listptr *list) {
	Listptr temp, current, sorted = NULL; // Use a new pointer (sorted) to create the new sorted list
	current = *list;
	while (current != NULL) {
		temp = current->next;
		InsertSort(&sorted, current); // Sort the current node
		current = temp;
	}
	*list = sorted; // list pointer to the new sorted list
}

// Use a sorted list and insert the node to the correct place
void InsertSort(Listptr *list, Listptr node) {
	Listptr current;
	if (*list == NULL || (*list)->data > node->data) { // The node becomes the first element of the list
		node->next = *list;
		*list = node;
	}
	else {
		current = *list;
		while (current->next != NULL) {
			if (node->data < current->next->data) { // It is the place of the new node
				node->next = current->next;
				current->next = node;
				return;
			}
			current = current->next;
		}
		node->next = current->next; // Place node after current
		current->next = node;
	}
}
