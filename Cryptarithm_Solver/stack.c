#include <stdio.h>
#include "stack.h"

void Initialize(Stack *S) {
	S->count = 0;
}

int Empty(Stack *S) {
	return (S->count == 0);
}

int Full(Stack *S) {
	return (S->count == STACK_SIZE);
}

void Pop(Stack *S, StackItem *X) {
	if (S->count == 0)
		printf("\nThe stack is empty!!\n");
	else {
		(S->count)--;
		*X = S->items[S->count];
	}
}

void Push(Stack *S, StackItem X) {
	if (S->count == STACK_SIZE)
		printf("\nThe stack is full!!\n");
	else {
		S->items[S->count] = X;
		(S->count)++;
	}
}

int Size(Stack *S) {
	return (S->count);
}

int Search(Stack *S, StackItem num) {
	int i, size = Size(S);
	for (i = 0; i < size; i++) {
		if (S->items[i] == num) {
			return 1;
		}
	}
	return 0;
}

StackItem Find(Stack *S, int num) {
	return (S->items[num]);
}
