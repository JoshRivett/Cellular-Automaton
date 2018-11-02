/*
	Name: Josh Rivett
	Matric Number: 170005367
	Module Code: AC21009

	References:
		https://natureofcode.com/book/chapter-7-cellular-automata/
		https://www.tutorialspoint.com/cprogramming/
		https://stackoverflow.com/questions/31577866/c-convert-integer-to-binary-array
		https://stackoverflow.com/questions/17307275/what-is-the-printf-format-specifier-for-bool

	TODO:
		Option for 2D generations.
*/

#include "validation.h"
#include "1dCA.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* Function for displaying the menu options. */
int menu() {
	printf("\nMain Menu:");
	printf("\n1 - Rule 30 1-D Cellular Automaton");
	printf("\n2 - Custom 1-D Cellular Automaton");
	printf("\n0 - Quit Program");
	printf("\n");

	return 0;
}

/* Function for displaying the custom generations menu.
	width		- The current custom width.
	generations	- The current number of generations.
	rule		- The current custom rule.
	startingRow	- the row of cells to start with.
	wrap		- whether or not the generation should wrap the sides.
	writeToFile	- whether or not to write the output to a file.
*/
int customMenu(int width, int generations, int rule, int *startingRow, _Bool wrap, _Bool writeToFile) {
	printf("\nCustom 1-D Cellular Automaton Options:");
	printf("\n1 - Generate");
	printf("\n2 - Change Number of Cells for Custom Automaton (Current: %d)", width);
	printf("\n3 - Change Number of Generations for Custom Automaton (Current: %d)", generations);
	printf("\n4 - Change Rule for Custom Automaton (Current: %d)", rule);
	printf("\n5 - Change the Starting Row of Cells (Current: ");
	for (int i = 0; i < width; i++) {
		printf("%d", startingRow[i]);
	}
	printf(")");
	printf("\n6 - Toggle Side Wrap (Current: %s)", wrap ? "true" : "false");
	printf("\n7 - Toggle Writing to File (Current: %s)", writeToFile ? "true" : "false");
	printf("\n0 - Back to Main Menu\n");

	return 0;
}

/* Function for running the options menu. */
int customGeneration() {
	//Declares the required variables.
	int option = 0;
	int rowOption = 0;
	int cell = 0;
	int error = 0;
	int width = 31;
	int maxWidth = 128;
	int generations = 16;
	int rule = 30;
	int startingRow[maxWidth];
	_Bool wrap = 0;
	_Bool writeToFile = 0;

	//Sets the seed for random generations.
	srand(time(NULL));

	//Initialises the startingRow array.
	for (int i = 0; i < maxWidth; i++) {
		startingRow[i] = 0;
	}
	startingRow[width/2] = 1;

	do {
		//Displays the options menu and receives an option from the user.
		customMenu(width, generations, rule, startingRow, wrap, writeToFile);
		printf("\nEnter menu option: ");
		option = validInt();

		//Runs the code relevant to the option the user selected.
		switch(option) {
			case 1:
				//Runs the 1-D cellular automaton with the supplied parameters.
				error = generate(width, generations, rule, startingRow, wrap, writeToFile);
				
				//Displays the relevant error message.
				if (error == BAD_FILE) {
					printf("Could not open file.");
				} else {
					printf("\nFinished generation.\n");
				}
				break;
			case 2:
				//Receives a custom number of cells from the user.
				printf("\nEnter the number of cells for each row: ");
				width = validInt();

				//Makes sure the width is at least 1 and less than the maxWidth.
				while (width < 1 || width > maxWidth) {
					printf("Width must be between 1 and %d: ", maxWidth);
					width = validInt();
				}

				//Resets the startingRow array..
				for (int i = 0; i < width; i++) {
					startingRow[i] = 0;
				}
				startingRow[width/2] = 1;
				break;
			case 3:
				//Receives a custom number of rows from the user.
				printf("\nEnter the number of rows to generate: ");
				generations = validInt();

				//Makes sure the number of generations is at least 1.
				while (generations < 0) {
					printf("Rows must be at least 1: ");
					generations = validInt();
				}
				break;
			case 4:
				//Receives a custom rule from the user.
				printf("\nEnter the rule for cell generation: ");
				rule = validInt();

				//Makes sure the rule is within the valid range of values.
				while (rule < 0 || rule > 255) {
					printf("Rule must be a number between 0 and 255: ");
					rule = validInt();
				}
				break;
			case 5:
				//Runs the custom starting row menu.
				do {
					//Displays the custom starting row menu.
					printf("\nCustom Starting Row Options (Current: ");
					for (int i = 0; i < width; i++) {
						printf("%d", startingRow[i]);
					}
					printf(")");
					printf("\n1 - Set to Middle");
					printf("\n2 - Set Specific Bit");
					printf("\n3 - Randomise");
					printf("\n0 - Back to Custom Menu\n");

					//Receives an option from the user.
					printf("\nEnter menu option: ");
					rowOption = validInt();

					switch(rowOption) {
						case 1:
							//Sets the starting bit to the middle of the row.
							for (int i = 0; i < width; i++) {
								startingRow[i] = 0;
							}
							startingRow[width/2] = 1;
							printf("\nStarting bit set to middle.\n");
							break;
						case 2:
							//Toggles the bit specified by the user.
							printf("\nEnter cell to toggle: ");
							cell = validInt();

							while (cell < 0 || cell > width - 1) {
								printf("Cell must be within 0 and %d: ", width - 1);
								cell = validInt();
							}

							if (startingRow[cell] == 0) {
								startingRow[cell] = 1;
								printf("\nCell %d set to 1.\n", cell);
							} else {
								startingRow[cell] = 0;
								printf("\nCell %d set to 0.\n", cell);
							}
							break;
						case 3:
							//Randomises the starting row of cells.
							for (int i = 0; i < width; i++) {
								startingRow[i] = rand() % 2;
							}
							printf("\nStarting row randomised.\n");
							break;
						case 0:
							printf("\nReturning to custom menu...\n");
							break;
						default:
							printf("\nInvalid menu option.\n");
							break;
					}
				} while (rowOption != 0);
				break;
			case 6:
				//Switches the wrap variable to be true if false and vice versa.
				if (wrap == 0) {
					wrap = 1;
					printf("\nSide wrap set to true.\n");
				} else {
					wrap = 0;
					printf("\nSide wrap set to false.\n");
				}
				break;
			case 7:
				//Switches the writeToFile variable to be true if false and vice versa.
				if (writeToFile == 0) {
					writeToFile = 1;
					printf("\nWriting to file set to true.\n");
				} else {
					writeToFile = 0;
					printf("\nWriting to file set to false.\n");
				}
				break;
			case 0:
				printf("\nReturning to main menu...\n");
				break;
			default:
				printf("\nInvalid menu option.\n");
				break;
		}
	//Exits the menu loop if the user enters 0.
	} while (option != 0);

	return 0;
}

/* The main function of the program. */
int main() {
	//Declares the required variables.
	int option = 0;
	int width = 31;
	int generations = 16;
	int rule = 30;
	int startingRow[width];
	_Bool wrap = 0;
	_Bool writeToFile = 0;

	//Initialises the startingRow array.
	for (int i = 0; i < width; i++) {
		startingRow[i] = 0;
	}
	startingRow[width/2] = 1;

	do {
		//Displays the menu and receives an option from the user.
		menu();
		printf("\nEnter menu option: ");
		option = validInt();

		//Runs the code relevant to the option the user selected.
		switch(option) {
			case 1:
				//Runs the 1-D cellular automaton using the sample parameters.
				generate(width, generations, rule, startingRow, wrap, writeToFile);
				printf("\nFinished generation.\n");
				break;
			case 2:
				customGeneration();
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