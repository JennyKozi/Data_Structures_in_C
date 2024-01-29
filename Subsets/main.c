#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

#define SIZE 100

int solutions = 0;

void calculate(int *, Stack *);
int AllAssigned(int, Stack *);
void Solve(Stack *);
int Assign(int, Stack *);
void Unassign(Stack *);

int main(void) {
	int set[SIZE] = {0, 1, 2, 3};
	Stack st;
	
	Initialize(&st);
	printf("\n");
	calculate(set, &st);
	printf("\nFound %d solutions.\n", solutions);

	return 0;
}

void calculate(int set[], Stack *st) {
	int i;
	for (i = 0; i <= 3; i++) {
		if (Assign(i, st)) {
			Solve(st);
			calculate(set, st);
			Unassign(st);
		}
	}
}

int AllAssigned(int num, Stack *st) {
	int size = Size(st);
	if (size == num)
		return 1;
	return 0;
}

int Assign(int num, Stack *st) {
	if (Search(st, num)) {
		return 0;
	}
	else {
		Push(st, num);
		return 1;
	}
}

void Unassign(Stack *st) {
	int num;
	Pop(st, &num);
}

void Solve(Stack *st) {
	int stack_size = Size(st);
	int i;
	
	printf("{");
	for (i = 0; i < stack_size - 1; i++) {
		printf("%d, ", Find(st, i));
	}
	printf("%d}\n", Find(st, stack_size - 1));
	solutions++;
}
