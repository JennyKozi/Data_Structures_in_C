#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"

int main (void) {

	int i;
	SortingArray A;
	long curtime = time(NULL);

	srand(curtime);
	printf("\nArray:\n");
	for (i = 0; i < MAXCOUNT; i++) {
		A[i] = rand() % 1000; // The array is initialized by random numbers
		printf("%d ", A[i]);
	}
	printf("\n");
	PriorityQueueSort(A);
	printf("\nSorted Array:\n");

	for (i = 0; i < MAXCOUNT; i++){
		printf("%d ", A[i]);
	}
	printf("\n");

	return 0;
}
