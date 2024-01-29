#include <stdio.h>
#include <stdlib.h>
#include "doubly-linked-list.h"

typedef struct node {
	ListItem data;
	struct node *next;
	struct node *prev;
} ListNode;

//Requested Functions

// Create and initialize a new doubly linked list
void Create(Listptr *head, Listptr *list, Listptr *tail) {

	// Pointer to the start of the list
	*list = NULL;

	// Node head
	(*head) = malloc(sizeof(ListNode));
	if ((*head) == NULL) {
		printf("Cannot allocate memory!\n");
		exit(1);
	}
	(*head)->next = *list;
	(*head)->prev = NULL;

	// Node tail
	(*tail) = malloc(sizeof(ListNode));
	if ((*tail) == NULL) {
		printf("Cannot allocate memory!\n");
		exit(1);
	}
	(*tail)->prev = *list;
	(*tail)->next = NULL;
}

// Calculate and return the size of the list
int Size(Listptr list) {
	int count = 0;
	while (list != NULL) {
		count++;
		list = list->next;
	}
	return count;
}

// Return 1: the list is empty, Return 0: the list is not empty
int IsEmpty(Listptr list) {
	return (list == NULL);
}

// Return a pointer to the first node of the list by using the head node
Listptr GetFirst(Listptr head) {
	return (head->next);
}

// Return a pointer to the last node of the list by using the tail node
Listptr GetLast(Listptr tail) {
	return (tail->prev);
}

// Return a pointer to the node that is before the given node of the list
Listptr GetPrev(Listptr node) {
	if (node != NULL)
		return (node->prev);
	else
		return NULL;
}

// Return a pointer to the node that is before the given node of the list
Listptr GetNext(Listptr node) {
	if (node != NULL)
		return (node->next);
	else 
		return NULL;
}

// Add the new node z before the given node v
void AddBefore(Listptr *list, Listptr *head, Listptr *z, Listptr *v) {
	if (*v == NULL || *z == NULL || *list == NULL) { // Wrong input
		return;
	}
	if (((*v)->prev) != NULL) { // v isn't the first node of the list
		(*z)->next = *v;
		(*z)->prev = (*v)->prev;
		(*v)->prev->next = *z;
		(*v)->prev = *z;
	}
	else { // v is the first node of the list
		(*z)->next = *v;
		(*v)->prev = *z;
		(*head)->next = *z; // Node head must point to the new first node
		(*list) = *z;
	}
}

// Add the new node z after the given node v
void AddAfter(Listptr *tail, Listptr *z, Listptr *v) {
	if (*v == NULL || *z == NULL) { // Wrong input
		return;
	}
	if (((*v)->next) != NULL) { // v isn't the last node of the list
		(*z)->prev = *v;
		(*z)->next = (*v)->next;
		(*v)->next->prev = *z;
		(*v)->next = *z;
	}
	else { // v is the last node of the list
		(*z)->prev = *v;
		(*v)->next = *z;
		(*tail)->prev = *z; // Node tail must point to the new last node
	}
}

// Add a new first node to the list
void AddFirst(Listptr *list, Listptr *head, Listptr *tail, Listptr *newnode) {
	(*newnode)->next = *list;
	if ((*list) != NULL) {
		(*list)->prev = *newnode;
	}
	*list = *newnode; // The pointer to the list must point to the new first node
	(*head)->next = (*list); // Node head must point to the new first node
	if (Size(*list) == 1) // If this is the first node of the list, it is both the first and the last node
		(*tail)->prev = *list;
}

// Add a new node to the end of the list
void AddLast(Listptr *list, Listptr *head, Listptr *tail, Listptr *newnode) {
	if ((*list) == NULL) {
		*list = *newnode;
		(*head)->next = *list;
		(*tail)->prev = (*list);
	}
	else {
		(*newnode)->prev = (*tail)->prev;
		(*tail)->prev->next = (*newnode);
		(*tail)->prev = (*newnode);
	}	
}

// The fourth argument of the function is the node that will be deleted
int Remove(Listptr *list, Listptr *head, Listptr *tail, Listptr *node, ListItem *elem) {
	Listptr current = *node;
	if (IsEmpty(*list)) {
		printf("\nCannot delete an element because the list is empty!\n");
		return 0;
	}
	if ((*node) == NULL) {
		printf("\nCannot delete because the node does not exist!\n");
		return 0;
	}
	*elem = (*node)->data;
	if ((*node)->prev == NULL) { // If it's the first node
		(*list) = (*list)->next;
		(*head)->next = *list;
		if (*list != NULL)  // The list had more than one nodes
			(*list)->prev = NULL;
		else // The list had only one node
			(*tail)->prev = *list;
	}
	else if ((*node)->next == NULL) { // It's the last node and the list had more than one nodes
		(*tail)->prev = (*node)->prev;
		(*node)->prev->next = NULL;
	}
	else { // Not the first or the last node. The list had at least 3 nodes
		(*node)->prev->next = (*node)->next;
		(*node)->next->prev = (*node)->prev;
	}
	free(current);
	return 1;
}

// Print all of the nodes of the list
void Print(Listptr list) {
	Listptr current = list;
	printf("\nList:\n");
	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

// My Functions

// All of the nodes of the list are created from this function
void CreateNewNode(Listptr *newnode) {
	*newnode = malloc(sizeof(ListNode));
	if ((*newnode) == NULL) {
		printf("Cannot allocate memory!\n");
		exit(1);
	}
	(*newnode)->data = rand() % 1000; // The data is a random number
	(*newnode)->prev = NULL;
	(*newnode)->next = NULL;
}

// Print the data of the given node
void PrintNode(Listptr node) {
	if (node != NULL)
		printf("%d\n", node->data);
}

// Print the list in reverse
void PrintReverse(Listptr tail) {
	Listptr current = (tail->prev);
	printf("\nList in reverse:\n");
	while (current != NULL) {
		printf("%d ", current->data);
		current = current->prev;
	}
	printf("\n");
}

// Find and return a pointer to the first node with data that is divided by div
Listptr FindNode(Listptr list, int div) {
	Listptr temp = list;
	while (temp != NULL) {
		if ((temp->data) % div == 0) {
			return temp;
		}
		temp = temp->next;
	}
	return temp;
}

// Return a pointer to the node that is indicated by num
Listptr GetNode(Listptr list, int num) {
	Listptr current = list;
	int i;
	for (i = 0; i < num - 1; i++) {
		if (current != NULL)
			current = current->next;
		else
			break;
	}
	return current;
}

// Free memory
void FreeList(Listptr *L, Listptr *head, Listptr *tail) {
	Listptr temp;
	free(*head);
	free(*tail);
	while ((*L) != NULL) {
		temp = (*L)->next;
		free(*L);
		*L = temp;
	}
}
