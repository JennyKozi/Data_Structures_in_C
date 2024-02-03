#include <stdio.h>
#include <stdlib.h>
#include "2-4tree.h"

struct STnode {
	Item keys[SIZE];
	link links[SIZE + 1];
};

link head;
Item result;
int count = 0, total = 0;

// Initialize tree
void STinit(void) {
	head = Create();
}

// Create a new empty node
link Create(void) {
	int i;
	link x = malloc(sizeof *x);

	if (x == NULL) {
		printf("Cannot allocate memory!\n");
		exit(1);
	}
	for (i = 0; i < SIZE; i++) {
		x->keys[i] = NULLITEM; // In the beginning every key is a NULLITEM
	}
	for (i = 0; i < SIZE + 1; i++) {
		x->links[i] = NULL; // In the beginning every link points to NULL
	}
	return x;
}

// Count the keys of the tree
int STcount(void) {
	count = 0;
	Count_Items(head);
	return count;
}

// Recursive function that goes through every node of the tree and counts the keys that are not NULLITEM
void Count_Items(link h) {
	int i, j, n;

	for (i = 0; i < SIZE; i++) {  // Check if the node is a leaf
		if (h->links[i] == NULL) {
			break;
		}
	}
	if (i == 0) {  // It's a leaf
		for (j = 0; j < SIZE; j++) {
			if (h->keys[j] != NULLITEM)
				count++;
		}
	}
	else if (i == 2) { // It has two nodes
		for (n = 0; n < i; n++) {
			Count_Items(h->links[n]);
			if (h->keys[n] != NULLITEM)
				count++;
		}
	}
	else if (i == 3) { // It has three nodes
		for (n = 0; n < i; n++) {
			Count_Items(h->links[n]);
			if (h->keys[n] != NULLITEM)
				count++;
		}
	}
	else if (i == 4) { // It has four nodes
		for (n = 0; n < i; n++) {
			Count_Items(h->links[n]);
			if (h->keys[n] != NULLITEM)
				count++;
		}
	}
}

// Search a key in the tree
int STsearch(Item key) {
	return Search_Item(head, key);
}

// Recursive function that goes through every node of the tree and returns 1 if it finds the requested key or 0 if the key does not exist
int Search_Item(link h, Item v) {
	int i;

	if (h == NULL) { // The key does not exist
		return 0;
	}
	for (i = 0; i < SIZE; i++) {
		if (v == h->keys[i]) // The key has been found
			return 1;
	}
	// Follow the right path according to where the requested key is supposed to be
	if (v < h->keys[0] || h->keys[0] == NULLITEM) {
		Search_Item(h->links[0], v);
	}
	else if (v < h->keys[1] || h->keys[1] == NULLITEM) {
		Search_Item(h->links[1], v);
	}
	else if (v < h->keys[2] || h->keys[2] == NULLITEM) {
		Search_Item(h->links[2], v);
	}
	else {
		Search_Item(h->links[3], v);
	}
}

// Find the (index)th smallest item of the tree
Item STselect(int index) {
	result = NULLITEM;
	total = 0;
	Select_Item(head, index);
	return result;
}

// Recursive function that goes through every node of the tree until it finds the (index)th smallest item
void Select_Item(link h, int index) {
	int i, j, n;
	
	// Check if the node is a leaf, a 2-node, a 3-node or a 4-node
	for (i = 0; i < SIZE; i++) {  // Check if the node is a leaf
		if (h->links[i] == NULL) {
			break;
		}
	}

	// It is a (2,4) tree, so there are 4 cases for its nodes:
	if (i == 0) {  // It's a leaf
		for (j = 0; j < SIZE; j++) {
			if (h->keys[j] != NULLITEM) {
				total++;
				if (total == index) // The (index)th smallest item of the tree has been found
					result = h->keys[j];  // Store its value
			}
		}
	}
	else if (i == 2) { // It has two nodes (children)
		for (n = 0; n < i; n++) {
			Select_Item(h->links[n], index);
			if (h->keys[n] != NULLITEM) {
				total++;
				if (total == index)
					result = h->keys[j];
			}
		}
	}
	else if (i == 3) { // It has three nodes
		for (n = 0; n < i; n++) {
			Select_Item(h->links[n], index);
			if (h->keys[n] != NULLITEM) {
				total++;
				if (total == index)
					result = h->keys[j];
			}
		}
	}
	else if (i == 4) { // It has four nodes
		for (n = 0; n < i; n++) {
			Select_Item(h->links[n], index);
			if (h->keys[n] != NULLITEM) {
				total++;
				if (total == index)
					result = h->keys[j];
			}
		}
	}
}

// Print the keys of the tree in sorted order
void STsort(void) {
	Print_Sorted (head);
}

// Recursive function that goes through every node of the tree and prints its keys in the correct order
void Print_Sorted(link h) {
	int i, j, n;
	for (i = 0; i < SIZE; i++) {  // Check if the node is a leaf
		if (h->links[i] == NULL) {
			break;
		}
	}
	if (i == 0) {  // It's a leaf
		for (j = 0; j < SIZE; j++) {
			if (h->keys[j] != NULLITEM)
				printf("%d ", h->keys[j]);
		}
	}
	else if (i == 2) { // It's a 2-node
		for (n = 0; n < i; n++) {
			Print_Sorted(h->links[n]);
			if (h->keys[n] != NULLITEM)
				printf("%d ", h->keys[n]);
		}
	}
	else if (i == 3) { // It's a 3-node
		for (n = 0; n < i; n++) {
			Print_Sorted(h->links[n]);
			if (h->keys[n] != NULLITEM)
				printf("%d ", h->keys[n]);
		}
	}
	else if (i == 4) { // It's a 4-node
		for (n = 0; n < i; n++) {
			Print_Sorted(h->links[n]);
			if (h->keys[n] != NULLITEM)
				printf("%d ", h->keys[n]);
		}
	}
}

void STinsert(Item key) {
	head = Insert_Tree(head, key);
	head = Root_Overflow(head); // Check for root overflow
}

// Recursive function that inserts every new key in the node that it belongs
link Insert_Tree(link h, Item key) {
	int i;

	if (h == NULL) {
		h = Create();
		h = Insert_Key(h, key);
		return h;
	}
	else {
		for (i = 0; i < SIZE; i++) {  // Check if the node is a leaf
			if (h->links[i] != NULL) {
				break;
			}
		}
		if (i == SIZE) {  // It's a leaf
			h = Insert_Key(h, key);
			return h;
		}
		// Find out which one is the correct node to head to according to comparisons
		else {  // A node that is not a leaf
			if (key < h->keys[0] || h->keys[0] == NULLITEM || h->links[0] == NULL) {
				h->links[0] = Insert_Tree(h->links[0], key);
		}
			else if (key < h->keys[1] || h->keys[1] == NULLITEM || h->links[1] == NULL) {
				h->links[1]=Insert_Tree(h->links[1], key);
		}
			else if (key < h->keys[2] || h->keys[2] == NULLITEM || h->links[2] == NULL) {
				h->links[2] = Insert_Tree(h->links[2], key);
		}
			else if (key < h->keys[3] || h->keys[3] == NULLITEM || h->links[3] == NULL) {
				h->links[3] = Insert_Tree(h->links[3], key);
			}
			else {
				h->links[4] = Insert_Tree(h->links[4], key);
			}
		}
		h = Check_Overflow(h); // This is a parent and after the insertion one of its children may have an overflow
	}
	return h;
}

// We need to insert a key to the array of keys of the node
// The keys in the array of every node must be sorted
link Insert_Key(link h, Item key) {
	int i, j, s, temp, index;

	// Place the key in the array in the first available node
	for (s = 0; s < SIZE; s++) {
		if (h->keys[s] == NULLITEM) {
			h->keys[s] = key;
			break;
		}
	}

	// If the array has only one key then there is no need for the sorting operation
	if (h->keys[1] == NULLITEM) {
		return h;
	}

	// Sort the array of keys with Selection Sort
	for (i = 0; i < s + 1; i++) { // Selection Sort
		index = i;
		for (j = i + 1; j < s + 1; j++) {
			if (h->keys[j] < h->keys[index]) {
				index = j;
			}
		}
		temp = h->keys[i];
		h->keys[i] = h->keys[index];
		h->keys[index] = temp;
	}
	return h;
}

// After it has been found that a node, that is not the root, has overflow we split the nodes 
link Rearrange(link parent, int num) { // With the variable num we know which child of the node parent has an overflow
	int i, j;
	link temp_link1, temp_link2;
	Item temp_item;

	// Insert the third key of the child with overflow to the array of keys of the parent
	parent = Insert_Key(parent, parent->links[num]->keys[2]);

	// Check if all of the children that come after the child with the overflow are NULL pointers
	for (i = num + 1; i < SIZE + 1; i++) {
		if (parent->links[i] != NULL)
			break;
	}
	// If they are not then move the links one place further in the array and free the link that will be used in the split
	if (i != SIZE + 1) {
		for (j = SIZE; j > num + 1; j--) {
			parent->links[j] = parent->links[j - 1];
		}
		parent->links[j] = NULL;
	}

	temp_item = parent->links[num]->keys[3]; // Keep the key that will be inserted in the parent
	parent->links[num]->keys[2] = NULLITEM;  // Delete third and fourth keys from current child with overflow
	parent->links[num]->keys[3] = NULLITEM;
	
	temp_link1 = parent->links[num]->links[3]; // Keep fourth and fifth links that will become the children of a new node after the split
	temp_link2 = parent->links[num]->links[4];
	parent->links[num]->links[3] = NULL;  // Delete fouth and fifth keys from current child with overflow
	parent->links[num]->links[4] = NULL;
	
	parent = Insert_Tree(parent, temp_item); // Insert the fourth key of the child with overflow to a new node-sibling that will be created
	parent->links[num + 1]->links[0] = temp_link1;  // The children of the new node
	parent->links[num + 1]->links[1] = temp_link2;

	return parent;
}

// Check if a node has overflow
int Node_Overflow(link h) {
	if (h->keys[3] == NULLITEM) // key[3] of a node must always be a NULLITEM because a node can have up to 3 numbers
		return 0;
	else
		return 1;
}

// Check if one of the children of a node has overflow
link Check_Overflow (link h) {
	int i, j;

	for (i = 0; i < SIZE; i++) {
		if (h->links[i] != NULL) {
			if (Node_Overflow(h->links[i])) { // We have found the child with the overflow
				h = Rearrange(h, i);
				break;
			}
		}
	}
	return h;
}

// Check if the root has overflow after the insertion of a key and make the necessary changes
link Root_Overflow(link h) {
	link x, y;

	if (Node_Overflow(h)) {
		x = Create();  // New root
		x = Insert_Tree(x, h->keys[2]); // Insert the third key of the root to the new root
		y = Create();
		y = Insert_Tree(y, h->keys[3]); // Insert the fourth key of the root to the right child of the new root
		y->links[0] = h->links[3];  // Move the fourth and fifth links of node h to the right child of the new root
		y->links[1] = h->links[4];
		h->links[3] = NULL;
		h->links[4] = NULL;
		h->keys[2] = NULLITEM;  // Delete the third and fourth keys from node h
		h->keys[3] = NULLITEM;
		x->links[0] = h;  // h is the left child of the new root x
		x->links[1] = y;  // y is the right child of the new root x
		return x;
	}
	else
		return h;
}

// Delete tree
void STdelete_Tree(void) {
	Delete(head);
	printf("\nThe tree has been deleted!\n");
}

// Free memory
void Delete(link h) {
	int i;
	link tree = h;

	for (i = 0; i <= SIZE; i++) {
		if (tree->links[i] != NULL) {
			Delete(tree->links[i]);
		}
		else {
			free(tree);
			return;
		}
	}
}