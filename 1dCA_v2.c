/*
	Name: Justas Samuolis
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define dark "\x1B[5;30;40m \x1B[0m"
#define light " "

void decToBinary(int dec, _Bool **newarr, int N) {
  int k;
  *newarr = malloc(N);
  int c = 0;
  for (int i = N-1; i >= 0; i--) {
    k = dec >> i;
    (*newarr)[c++] = k & 1;
  }
}

void nextGen(_Bool **arr, _Bool binaryRule[], int N) {
	_Bool x, y, z;
	_Bool *tempArr = malloc(N);
	if (tempArr == NULL) {
		printf("Memory allocation failed; Check void generate()");
		return;
	}

	for (int i = 0; i < N; i++) {
		x = i - 1 >= 0 ? (*arr)[i-1] : (*arr)[N-1];
		y = (*arr)[i];
		z = i + 1 < N ? (*arr)[i+1] : (*arr)[0];
		tempArr[i] = binaryRule[7 - (x * 4 + y * 2 + z)];
	}

	free(*arr);
	*arr = tempArr;
}

void printGen(_Bool arr[], int N) {
	for (int i = 0; i < N; i++) {
		printf(arr[i] ? dark : light);
	}
	printf("\n");
}

void generate(int width, int generations, int rule) {
	_Bool *binaryRule = NULL, *gen = malloc(width);
	if (gen == NULL) {
		printf("Memory allocation failed; Check void generate()");
		return;
	}

	for (int i = 0; i < width; i++) {
		gen[i] = NULL;
	}
	gen[width/2] = 1;
	decToBinary(rule, &binaryRule, 8);

	for (int g = 0; g < generations; g++) {
		printGen(gen, width);
		nextGen(&gen, binaryRule, width);
	}
	
	free(binaryRule);
	free(gen);
}

int main() {
	clock_t start = clock(), diff;
	generate(150, 100, 30);
	diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);

	return 0;
}