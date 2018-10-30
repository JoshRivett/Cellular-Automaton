/*
	Name: Josh Rivett
	Matric Number: 170005367
	Module Code: AC21009
*/

#include <stddef.h>

/* Error Codes */
#define SUCCESS		100 //Successful completion of a function with nothing else to return.

/* Function for creating a new generation.
	width		- the number of cells on each row.
	generations	- the number of rows to generate.
	rule		- the rule to use for cell generation.
	wrap		- whether or not the generation should wrap the sides.
*/
int generate(int width, int generations, int rule, _Bool wrap);


/* Function for checking what state a cell should be in a new generation.
	left	- the cell to the top-left of the new cell.
	middle	- the cell directly above the new cell.
	right	- the cell to the top-right of the new cell.
	rule	- the rule to use for cell generation.
*/
int rules(int left, int middle, int right, int rule);


/* Function for converting a decimal number to a binary array.
	decimal	- the decimal number to be converted.
*/
int toBinary(int decimal);