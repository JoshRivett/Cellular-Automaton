/*
	Name: Josh Rivett
	Matric Number: 170005367
	Module Code: AC21009

	References:
		http://jackstromberg.com/2013/02/how-to-validate-numeric-integer-input-in-c/
*/

#include "validation.h"
#include <stdlib.h>
#include <stdio.h>

/* Function receiving a valid integer from the user.
	Returns a valid integer.
*/
int validInt() {
	//Declares the required variables.
	int validInt;
	int temp;

	//Loops until a valid integer is input.
	while (scanf("%d", &validInt) != 1){
		//Loops through the input until the end is reached.
		while ((temp = getchar()) != EOF && temp != '\n');
		printf("Enter a valid integer: ");
	}

	return validInt;
}