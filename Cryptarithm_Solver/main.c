#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

#define SIZE 10

int count = 0;
int solutions = 0;

void addletters(char *, char *);
void calculate(char *, char *, char *, char *, Stack *);
int AllAssigned(char *, Stack *);
void Solve(char *, char *, char *, char *, Stack *);
int Assign(int, Stack *);
void Unassign(Stack *);
int power(int, int);

int main(void) {
	char word1[SIZE], word2[SIZE], word3[SIZE], letters[SIZE];
	int i, length;
	int values[SIZE];
	Stack st;

	Initialize(&st);
	for (i = 0; i < SIZE; i++) {
		letters[i] = '\0';
	}

	// Insert the words and store the letters to a string
	printf("\nInsert first word (1-9 letters):\n\n");
	fgets(word1, SIZE, stdin);
	printf("+\n");
	fgets(word2, SIZE, stdin);
	printf("=\n");
	fgets(word3, SIZE, stdin);

	// Add every new letter from the words to the array letters
	addletters(word1, letters);
	addletters(word2, letters);
	addletters(word3, letters);

	printf("\nDifferent Letters: %d\n", count); // Print all of the different letters
	length = strlen(letters);
	printf("\nLetters: ");
	for (i = 0; i < length; i++) {
		printf("%c ", letters[i]);
	}
	printf("\n");
	calculate(word1, word2, word3, letters, &st); // Call recursive function
	printf("\nFound %d solutions.\n", solutions);

	return 0;
}

int power(int base, int n) {
	int p;
	for (p = 1; n > 0; n--) { // base^n equals to
		p *= base; // base*base*...*base (n times)
	}
	return p;
}

// Find if the given word has any new letters an add them to the array letters
void addletters(char str[], char letters[]) {
	int i, j, l, s;

	for (i = 0; str[i] != '\n'; i++) {
		l = strlen(letters);
		for (j = 0; j < l; j++) {
			if (letters[j] == str[i]) { // Search if the letter str[i] already exists in the array letters[]
				break;
			}
		}
		if (j == l) {
			if (count == SIZE) { // No more than 10 different letters
				printf("\nCannot have more than %d different letters!\n", SIZE);
				exit(1);
			}
			for (s = 0; s < SIZE; s++) {
				if (letters[s] == '\0') {
					letters[s] = str[i];
					count++;
					break;
				}
			}
		}
	}
}

// Recursive function that checks every case to see if there is a solution
void calculate(char word1[], char word2[], char word3[], char letters[], Stack *st) {
	int i;
	if (AllAssigned(letters, st)) { //All of the letters have been matched with a number
		Solve(word1, word2, word3, letters, st); // Check the current case
		return;
	}
	for (i = 0; i <= 9; i++) { // The numbers 0-9
		if (Assign(i, st)) {
			calculate(word1, word2, word3, letters, st);
			Unassign(st);
		}
	}	
}

// Check if the stack has as many numbers as the number of letters
int AllAssigned(char letters[], Stack *st) {
	int size = Size(st);
	int l = strlen(letters);
	if (size == l)
		return 1;
	return 0;
}

// Add a number to the stack
int Assign(int num, Stack *st) {
	if (Search(st, num)) {
		return 0;
	}
	else {
		Push(st, num);
		return 1;
	}
}

// Remove a number fron the stack
void Unassign(Stack *st) {
	int num;
	Pop(st, &num);
}

// Take a given case and check if it is a solution
void Solve(char word1[], char word2[], char word3[], char letters[], Stack *st) {
	int num1[SIZE], num2[SIZE], num3[SIZE];
	int values[SIZE];
	int i, j, s = 0, number1 = 0, number2 = 0, number3 = 0;

	// The number of letters that the strings have
	int length = strlen(letters);
	int l1 = strlen(word1) - 1;
	int l2 = strlen(word2) - 1;
	int l3 = strlen(word3)- 1;

	for (i = 0; i < SIZE; i++) {
		num1[i] = 0;
		num2[i] = 0;
		num3[i] = 0;
	}
	for (i = 0; i < length; i++) {
		values[i] = Find(st, i); // Create an array with the elements of the stack in the same order
	}

	// Based on the arrays letters[] and values[], match each letter with a number and create an array num[] for every word
	// The array num[] shows the number that is represented by each word
	for (i = 0; i < length; i++) {
		for (j = 0; j < l1; j++) {
			if (word1[j] == letters[i]) { // values[i] shows the number that is represented by the letter[i]
				if (j == 0 && values[i]== 0) // The first letter of a word cannot be 0
					return;
				else 
					num1[j] = values[i]; // num[j] is the number that is represented by word[j]
			}
		}
		for (j = 0; j < l2; j++) {
			if (word2[j] == letters[i]) {
				if (j == 0 && values[i] == 0) // The first letter of a word cannot be 0
					return;
				else 
					num2[j] = values[i];
			}
		}
		for (j = 0; j < l3; j++) {
			if (word3[j] == letters[i]) {
				if (j == 0 && values[i] == 0) // The first letter of a word cannot be 0
					return;
				else 
					num3[j] = values[i];
			}
		}
	}

	// Create the three numbers for the addition
	for (i = l1 - 1; i >= 0; i--) {
		number1 = number1 + num1[i] * power(10, s);
		s++;
	}
	s = 0;
	for (i = l2 - 1; i >= 0; i--) {
		number2 = number2 + num2[i] * power(10, s);
		s++;
	}
	s = 0;
	for (i = l3 - 1; i >= 0; i--) {
		number3 = number3 + num3[i] * power(10, s);
		s++;
	}

	// Check if the addition is correct
	if (number3 == number1 + number2) {
		solutions++; // A solution has been found
		printf("\nSolution %d: %d + %d = %d\n", solutions, number1, number2, number3);
		for (i = 0; i < length; i++) {
			printf("%c=%d  ", letters[i], values[i]);
		}
		printf("\n");
	}
}
