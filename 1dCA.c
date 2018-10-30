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
	int i = 0;
	int ruleset[8];

	//Initialises the ruleset array.
	for (int i = 0; i < 8; i++) {
		ruleset[i] = 0;
	}

	//Converts the rule to an array of binary digits.
	while (rule > 0) {
		ruleset[i] = rule % 2;
		i++;
		rule /= 2;
	}

	//Creates a binary string based on the 3 input parameters.
	char binary[3] = {left + '0', middle + '0', right + '0'};
	char *ptr;
	long decimal;

	//Converts the binary string to a long int.
	decimal = strtol(binary, &ptr, 2);

	//Returns the state of the new cell according to the ruleset.
	return ruleset[decimal];
}