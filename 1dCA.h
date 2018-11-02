/*
	Name: 			Josh Rivett	Naqash Nadeem	Justas Samuolis
	Matric Number:	170005367	160010238		170020434
	Module Code:	AC21009
*/

#include <stddef.h>

/* Error Codes */
#define SUCCESS		100 //Successful completion of a function with nothing else to return.
#define BAD_FILE	101 //The file could not be opened.

#define dark "\x1B[5;30;40m \x1B[0m"
#define light " "

/* Function for creating a new generation.
	width		- the number of cells on each row.
	generations	- the number of rows to generate.
	rule		- the rule to use for cell generation.
	startingRow	- the row of cells to start with.
	wrap		- whether or not the generation should wrap the sides.
	writeToFile	- whether or not to write the output to a file.
*/
int generate(int width, int generations, int rule, int *startingRow, _Bool wrap, _Bool writeToFile);


/* Function for checking what state a cell should be in a new generation.
	left	- the cell to the top-left of the new cell.
	middle	- the cell directly above the new cell.
	right	- the cell to the top-right of the new cell.
	rule	- the rule to use for cell generation.
*/
int rules(int left, int middle, int right, int rule);


/* Function for converting a decimal number to a binary array.
	decimal	- the decimal number to be converted.
	*binary	- the array to store the binary number in.
*/
int toBinary(int decimal, int *binary);


/* Function to convert an array of binary integers to a decimal number.
	*binaryInt	- pointer to an array of binary integers.
	length		- the length of the array.
	Returns the decimal equivalent to the binary number passed in.
*/
int toDecimal(int *binaryInt, int length);