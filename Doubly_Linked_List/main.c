#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "doubly-linked-list.h"

int main(void) {
	Listptr list, head, tail, newnode, current, z, v;
	ListItem elem;
	int i, index;
	
	srand(time(NULL));
	Create(&head, &list, &tail);
	
	if (IsEmpty(list)) {
		printf("\nThe list is empty!\n");
	}
	
	printf("\nInsert at start:\n");
	for (i = 0; i < 4; i++) {
		CreateNewNode(&newnode);
		AddFirst(&list, &head, &tail, &newnode);
		Print(list);
	}
	
	printf("\nInsert at end:\n");
	for (i = 0; i < 3; i++) {
		CreateNewNode(&newnode);
		AddLast(&list, &head, &tail, &newnode);
		Print(list);
	}
	
	printf("\nAdd a node after the first even number:\n");
	v = FindNode(list, 2);  // v is the given node

	if (v != NULL) {
		CreateNewNode(&z); // z is the new node
		AddAfter(&tail, &z, &v);
		Print(list);	
	}

	printf("\nAdd a node before the first number that is divided by 3:\n");
	v = FindNode(list, 3); // v is a node that already exists

	if (v != NULL) {
		CreateNewNode(&z);
		AddBefore(&list, &head, &z, &v);
		Print(list);
	}

	index = 3;
	v = GetNode(list, index);

	if (v != NULL) {
		printf("\nNode %d with element ", index);
		PrintNode(v);
		printf("\nNode %d with element ", index - 1);
		PrintNode(GetPrev(v)); // Get the node that is before node v and print its data
	}
	else
		printf("\nThe node %d does not exist!\n", index);
	
	printf("\nInsert node's index: ");
	scanf("%d", &index); // Insert the index (starting from 1) of the node that will be used
	v = GetNode(list, index);

	if (v != NULL) {
		current = GetNext(v); // Current is the node after v
		if (current != NULL) {
			printf("\nNode %d with element ", index);
			PrintNode(v); // Print data of v
			printf("\nNode %d with element ", index + 1);
			PrintNode(current); // Print data of current
		}
		else {
			printf("\nCannot find an element after ");
			PrintNode(v);
		}
	}
	else
		printf("\nThe node %d does not exist!\n", index);

	printf("\nFirst Node's element: ");
	PrintNode(GetFirst(head)); // Get the first node and print its data

	printf("\nLast Node's element: ");
	PrintNode(GetLast(tail)); // Get the last node and print its data

	printf("\nSize: %d elements\n", Size(list));
	PrintReverse(tail); // Print the list in reverse
	
	if (Remove(&list, &head, &tail, &list, &elem)) {
		printf("\nRemove first node: element %d was removed!\n", elem);
		Print(list);
	}

	current = GetLast(tail);
	if (Remove(&list, &head, &tail, &current, &elem)) {
		printf("\nRemove last node: element %d was removed!\n", elem);
		Print(list);
	}

	printf("\nInsert node's index: ");
	scanf("%d", &index); // Insert the index (starting from 1) of the node that will be deleted
	v = GetNode(list, index);

	if (v != NULL) {
		if (Remove(&list, &head, &tail, &v, &elem)) {
			printf("\nNode with element %d was removed!\n", elem);
			Print(list);
		}
	}
	else
		printf("\nThe node %d does not exist!\n", index);
	
	FreeList(&list, &head, &tail); // Free memory

	return 0;
}
