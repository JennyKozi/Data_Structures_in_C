#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "2-4tree.h"

int main(void) {

	int maxN = 50, option = 1, i, index;
	Item key;
	srand(time(NULL));

	// STinit, STinsert
	STinit();
	if (!option) {
		printf("\nInsert keys:\n");
	}
	else {
		printf("\n");
	}
	for (i = 0; i < maxN; i++) {
		if (option) {
			key = rand() % 1000;
		}
		else {
			scanf("%d", &key);
		}
		if (!STsearch(key)) {
			printf("Inserting item %d\n", key);
			STinsert(key);
		}
		else {
			printf("\nCannot insert %d because it already exists!\n\n", key);
		}
	}

	// STsort
	printf("\nThe keys in sorted order are:\n");
	STsort();

	// STcount
	printf("\n\n%d keys were given\n", maxN);
	printf("\n%d distinct keys in the tree\n", STcount());

	// STselect
	index = 2; // index=[1...maxN]
	key = STselect(index);
	printf("\nThe %d smallest key is %d\n", index, key);

	// STsearch
	printf("\nSearch a number: ");
	scanf("%d", &key);
	if (!STsearch(key)) {
		printf("Key %d does not exist in the tree!\n", key);
	}
	else {
		printf("Key %d exists in the tree!\n", key);
	}

	// STdelete_Tree
	STdelete_Tree();

	return 0;
}
