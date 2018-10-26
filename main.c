/*
	Name: Josh Rivett
	Matric Number: 170005367
	Module Code: AC21009

	References:
		https://natureofcode.com/book/chapter-7-cellular-automata/
		https://www.tutorialspoint.com/cprogramming/
		https://stackoverflow.com/questions/31577866/c-convert-integer-to-binary-array

	TODO:
		Option to wrap sides.
		Option to write outputs to file.
		Option to customise the starting row.
		Option for 2D generations.
*/

#include "validation.h"
#include "1dCA.h"
#include <stdlib.h>
#include <stdio.h>

/* Function for displaying the menu options.
	width		- The current custom width.
	generations	- The current custom number of generations.
	rule		- The current custom rule.
*/
int menu(int width, int generations, int rule) {
	printf("\nMain Menu:");
	printf("\n1 - Rule 30 1-D Cellular Automaton");
	printf("\n2 - Custom 1-D Cellular Automaton (%d cells, %d generations, rule %d)", width, generations, rule);
	printf("\n\nCustom 1-D Cellular Automaton Options:");
	printf("\n3 - Change Number of Cells for Custom Automaton");
	printf("\n4 - Change Number of Generations for Custom Automaton");
	printf("\n5 - Change Rule for Custom Automaton");
	printf("\n\nOther:");
	printf("\n0 - Quit Program");
	printf("\n");

	return 0;
}

/* The main function of the program. */
int main() {
	//Declares the required variables.
	int option = 0;
	int width = 31;
	int generations = 16;
	int rule = 30;

	do {
		//Displays the menu and receives an option from the user.
		menu(width, generations, rule);
		printf("\nEnter menu option: ");
		option = validInt();

		//Runs the code relevant to the option the user selected.
		switch(option) {
			case 1:
				//Runs the 1-D cellular automaton using rule 30.
				generate(31, 16, 30);
				printf("\nFinished generation.\n");
				break;
			case 2:
				//Runs the 1-D cellular automaton with the supplied parameters.
				generate(width, generations, rule);
				printf("\nFinished generation.\n");
				break;
			case 3:
				//Receives a custom number of cells from the user.
				printf("\nEnter the number of cells for each row: ");
				width = validInt();

				//Makes sure the width is at least 1.
				while (width < 0) {
					printf("Width must be at least 1: ");
					width = validInt();
				}
				break;
			case 4:
				//Receives a custom number of rows from the user.
				printf("\nEnter the number of rows to generate: ");
				generations = validInt();

				//Makes sure the number of generations is at least 1.
				while (generations < 0) {
					printf("Rows must be at least 1: ");
					generations = validInt();
				}
				break;
			case 5:
				//Receives a custom rule from the user.
				printf("\nEnter the rule for cell generation: ");
				rule = validInt();

				//Makes sure the rule is within the valid range of values.
				while (rule < 0 || rule > 255) {
					printf("Rule must be a number between 0 and 255: ");
					rule = validInt();
				}
				break;
			case 0:
				printf("\nExiting program...\n");
				break;
			default:
				printf("\nInvalid menu option.\n");
				break;
		}
	//Exits the menu loop if the user enters 0.
	} while (option != 0);

	//Ends the program.
	return 0;
}