#include <stdio.h>
#include <stdlib.h>
#include "types.h"

// List: functions

// Create a new list
void Create_List(Listptr *list) {
	(*list) = NULL;
}

// Check if the list is empty
int IsEmpty_List(Listptr list) {
	return (list == NULL);
}

// Insert a new edge at start
int InsertAtStart_List(Listptr *list, ListItem num) {
	Listptr newnode, current;
	current = *list;
	
	newnode = malloc(sizeof(struct edge));
	if (newnode == NULL) {
		printf("Cannot allocate memory!\n");
		exit(1);
	}
	newnode->endpoint = num;
	newnode->nextedge=current;
	*list = newnode;
	return TRUE;
}

// Insert a new node after the ListItem x
int InsertAfter_List(Listptr p, ListItem x) {
	
	Listptr newnode = malloc(sizeof(Edge));

	if (newnode == NULL) {
		printf("Cannot allocate memory!\n");
		exit(1);
	}
	newnode->endpoint = x;
	newnode->nextedge = p->nextedge;
	p->nextedge = newnode;

	return TRUE;
}

// Ordered insert into the list
int Insert_List(Listptr *head, ListItem item) {
	Listptr prev, cur;

	if (*head == NULL) {
		return InsertAtStart_List(head, item);
	}
	else if (item < (*head)->endpoint) {
		return InsertAtStart_List(head, item);
	}
	else {
		cur = *head;
		while (1) {
			if (item == cur->endpoint) {
				return FALSE;
			}
			else if (item>cur->endpoint) {
				prev = cur;
				cur = cur->nextedge;
				if (cur == NULL)
					return InsertAfter_List(prev, item);
			}
			else
				return InsertAfter_List(prev, item);
		}
	}
}

// Print list
void Print_List(Listptr list) {
	Listptr temp = list;

	while (temp != NULL) {
		printf("%d ", temp->endpoint);
		temp = temp->nextedge;
	}
	printf("\n");
}

// Free memory
void Free_List(Listptr *list) {
	Listptr temp;
	while ((*list) != NULL) {
		temp = (*list)->nextedge;
		free(*list);
		*list = temp;
	}
}
