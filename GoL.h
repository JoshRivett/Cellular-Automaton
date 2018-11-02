/*
	Name: 			Josh Rivett	Naqash Nadeem	Justas Samuolis
	Matric Number:	170005367	160010238		170020434
	Module Code:	AC21009
*/

#include <stddef.h>

#define BORDER_TOP "____________________\n"
#define BORDER_BOT "--------------------\n"

// Function for printing a 2D board
void printBoard(_Bool **board, int rows, int cols, unsigned long generationCount, int FPS);

// Generates a random boolean
_Bool randomBool();

// Creates a delay
void delay(int milliSeconds);

void generateGoL(int fps);