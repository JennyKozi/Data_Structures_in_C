#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

struct PQueue {
	int Count;
	PQListNode* ItemList;
};

struct PQNodeTag {
	PQItem NodeItem;
	struct PQNodeTag *Link;
};

// Initialize PQ
void Initialize(PriorityQueue *PQ) {
	PQ->Count = 0;
	PQ->ItemList = NULL;
}

// Check if PQ is empty
int Empty(PriorityQueue *PQ) {
	return(PQ->Count == 0);
}

// Check if PQ is full
int Full(PriorityQueue *PQ) {
	return(PQ->Count == MAXCOUNT);
}

// Sort the array A
void PriorityQueueSort(SortingArray A) {
	int i;
	PriorityQueue PQ;
	Initialize(&PQ);
	for (i = 0; i < MAXCOUNT; i++)
		Insert(A[i], &PQ);
	for (i = MAXCOUNT - 1; i >= 0; i--)
		A[i] = Remove(&PQ);
}

// Insert an item to PQ by using the function SortedInsert to create a new PQListNode in the correct place  
void Insert(PQItem Item, PriorityQueue *PQ) {
	if (!Full(PQ)) {
		PQ->Count++;
		PQ->ItemList = SortedInsert(Item, PQ->ItemList);
	}
}

PQListNode *SortedInsert(PQItem Item, PQListNode *P) {
	PQListNode *N;
	if ((P == NULL) || (Item >= P->NodeItem)) {
		N = malloc(sizeof(PQListNode));
		if (N == NULL) {
			printf("Cannot allocate memory!\n");
			exit(1);
		}
		N->NodeItem = Item;
		N->Link = P;
		return N;
	}
	else {
		P->Link = SortedInsert(Item, P->Link);
		return P;
	}
}

// Delete an item and free memory
PQItem Remove(PriorityQueue *PQ) {
	PQItem temp;
	PQListNode *current;
	if (!Empty(PQ)) {
		temp = PQ->ItemList->NodeItem; // The item from the node that will be deleted
		current = PQ->ItemList; // Save the pointer
		PQ->ItemList = PQ->ItemList->Link; // The list points to the next element
		free(current); // Free memory
		return temp;
	}
}
