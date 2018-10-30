/*
	Name: Josh Rivett
	Matric Number: 170005367
	Module Code: AC21009
*/

#include "1dCA.h"
#include <stdlib.h>
#include <stdio.h>

/* Function for creating a new generation.
	width		- the number of cells on each row.
	generations	- the number of rows to generate.
	rule		- the rule to use for cell generation.
	wrap		- whether or not the generation should wrap the sides.		-
*/
int generate(int width, int generations, int rule, _Bool wrap) {
	//Modifies the input parameters as required.
	width += 2;
	generations -= 1;

	//Defines the parent and child arrays of cells.
	int parent[width];
	int child[width];

	//Initialises all the elements within the arrays as 0.
	for (int i = 0; i < width; i++) {
		parent[i] = 0;
		child[i] = 0;
	}

	//Sets the start state of the parent cells.
	parent[width/2] = 1;

	//Wraps the sides if side wrap is on.
	if (wrap == 1) {
		parent[0] = parent[width - 2];
		parent[width - 1] = parent[1];
	}

	//Takes a line break.
	printf("\n");

	//Prints the initial generation of the cells.
	for (int i = 1; i < width - 1; i++) {
		if (parent[i] == 0) {
			printf("   ");
		} else {
			printf(" # ");
		}
	}

	//Takes a line break.
	printf("\n");

	//Loops for the specified number of generations.
	for (int i = 0; i < generations; i++) {
		//Loops through each of the cells for the new generation.
		for (int j = 1; j < width - 1; j++) {
			//Determines the state for the current cell.
			child[j] = rules(parent[j-1], parent[j], parent[j+1], rule);

			//Prints the state of the current cell.
			if (child[j] == 0) {
				printf("   ");
			} else {
				printf(" # ");
			}
		}

		//Sets the new generation to be the new parent generation.
		for (int j = 0; j < width; j++) {
				parent[j] = child[j];
		}

		//Wraps the sides if side wrap is on.
		if (wrap == 1) {
			parent[0] = parent[width - 2];
			parent[width - 1] = parent[1];
		}

		//Takes a line break.
		printf("\n");
	}

	return SUCCESS;
}

/* Function for checking what state a cell should be in a new generation.
	left	- the cell to the top-left of the new cell.
	middle	- the cell directly above the new cell.
	right	- the cell to the top-right of the new cell.
	rule	- the rule to use for cell generation.
*/
int rules(int left, int middle, int right, int rule) {
	//Declares the required variables.
	int ruleset[8];
	int decimal;
	int binaryInt[3] = {left, middle, right};

	//Initialises the ruleset array.
	for (int i = 0; i < 8; i++) {
		ruleset[i] = 0;
	}

	//Converts the decimal rule to its bianry equivalent.
	toBinary(rule, ruleset);

	//Gets the decimal equivalent of the binary input parameters.
	decimal = toDecimal(binaryInt, 3);

	//Returns the state of the new cell according to the ruleset.
	return ruleset[decimal];
}

/* Function for converting a decimal number to a binary array.
	decimal	- the decimal number to be converted.
	*binary	- the array to store the binary number in.
*/
int toBinary(int decimal, int *binary) {
	int i = 0;

	//Converts the rule to an array of binary digits.
	while (decimal > 0) {
		binary[i] = decimal % 2;
		i++;
		decimal /= 2;
	}

	return SUCCESS;
}

/* Function to convert an array of binary integers to a decimal number.
	*binaryInt	- pointer to an array of binary integers.
	length		- the length of the array.
*/
int toDecimal(int *binaryInt, int length) {
	//Initialises the required variables.
	char binaryString[length];
	char *ptr;
	long decimal;

	//Converts the integer array to a character array.
	for (int i = 0; i < length; i++) {
		binaryString[i] = binaryInt[i] + '0';
	}

	//Converts the binary string to a long int.
	decimal = strtol(binaryString, &ptr, 2);

	return decimal;
}