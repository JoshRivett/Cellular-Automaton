/*
	Name: 			Josh Rivett	Naqash Nadeem	Justas Samuolis
	Matric Number:	170005367	160010238		170020434
	Module Code:	AC21009
*/

// https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
// https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
// https://stackoverflow.com/questions/276827/string-padding-in-c

#include "GoL.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/*
  Generates a pseudo-random Boolean number
*/
_Bool randomBool() {
  return rand() % 2 == 0;
}

/*
  Prints board to screen and displays FPS & generation count.
*/
void printBoard(_Bool **board, int rows, int cols, unsigned long generationCount, int FPS) {
  printf("\e[1;1H\e[2J");
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      printf(board[y][x] ? "x" : " ");
    }
    printf("\n");
  }
  
  printf(BORDER_TOP);
  printf("|%-18s|\n", " Generations:");
  printf("| %-17ld|\n", generationCount);
  printf("|%-18s|\n", " FPS/GenPerSec:");
  printf("| %-17d|\n", FPS);
  printf("|%-18s|\n", " CTRL+C To Exit");
  printf(BORDER_BOT);
}

struct timeval stop, start;
long int max = 0;
/*
  Delays the program
*/
void delay(int milliSeconds) 
{   
    // Stroing start time 
    gettimeofday(&start, NULL);

    long startTime = start.tv_sec * 1000000 + start.tv_usec + milliSeconds*1000;
    // looping till required time is not acheived 
    while (gettimeofday(&stop, NULL), stop.tv_sec * 1000000 + stop.tv_usec < startTime);
} 

/*
  Returns neighbor count for a board
*/
int neighborCount(_Bool **board, int x, int y, int rows, int cols) {
  int neighbors = 0;

  for (int i = - 1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      // wrap
      neighbors += board[(y+i < 0 ? rows-1 : y+i >= rows ? 0 : y+i)][(x+j < 0 ? cols-1 : x+j >= cols ? 0 : x+j)];
    }
  }

  return neighbors - board[y][x];
}

/* Function responsible for generating new stage of Game of Life
  and calling other functions (for printing to screen, etc..)
*/
void generateGoL(int fps) {
  // get terminal size
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  time_t t;
  srand((unsigned) time(&t));

  _Bool **board, **next;

  int rows = w.ws_row - 7;
  int cols = w.ws_col;

  // allocate rows and columns for the board
  board = malloc(rows * sizeof *board);
  next = malloc(rows * sizeof *next);
  if (board == NULL || next == NULL) {
    printf("Could not allocate memory. Exiting...");
    return;
  }

  for (int i = 0; i < rows; i++) {
    board[i] = malloc(cols);
    next[i] = malloc(cols);
  }

  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      board[y][x] = randomBool();
    }
  }

  int neighbors;
  unsigned long int generationCount = 0;

  // inifinite loop for generating (going trough life-stages)
  while(1) {
    generationCount++;
    printBoard(board, rows, cols, generationCount, fps);

    for (int y = 0; y < rows; y++) {
      for (int x = 0; x < cols; x++) {
        neighbors = neighborCount(board, x, y, rows, cols);
        if (board[y][x] && (neighbors < 2 || neighbors > 3)) {
          next[y][x] = 0;
        }
        else if (!board[y][x] && neighbors == 3) next[y][x] = 1;
        else next[y][x] = board[y][x];
      }
    }

    for (int y = 0; y < rows; y++)
      for (int x = 0; x < cols; x++)
        board[y][x] = next[y][x];
    
    delay(1000/fps);
  }
  

  // free memory
  for (int i = 0; i < rows; i++) {
    free(board[i]);
    free(next[i]);
  }
  free(board);
  free(next);
}