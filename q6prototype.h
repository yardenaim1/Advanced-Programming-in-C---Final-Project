#ifndef Q6PROT_H
#define Q6PROT_H

#include "definitions.h"

/*
	The main function of question #6 -  creates a list of moves from receieved file.
	Returns different values depending on cases where list is invalid/covers the whole board or not.
	In case list is valid, uses 'display' function from Q2 to print the moves of the list
*/
int checkAndDisplayPathFromFile(char *file_name, movesArray **moves, char **board); 

movesList fileToList(FILE* file, short int size, boardPos start); // Creates the list using various case functions & initializes 'start' value

void createStartPos(FILE* file, int * row, int* col, boardPos start); // Initializes 'start' values and updates indices row & col

/*	These functions behave similarly but handle all 4 different cases where we need to extract the data of the square and translate it to actual values:

	Case 0 handles situations where the 6 bits of the square to extract are all in one byte, and are bits 2-7.
	Case 1 handles situations where the 6 bits to extract are spread across 2 bytes - bits 0-1 in previous byte and bits 4-6 in current byte.
	Case 2 handles situations where the 6 bits to extract are spread across 2 bytes - bits 0-3 in previous byte and bits 6-7 in current byte.
	Case 3 handles situations where the 6 bits to extract are all in one byte, and are bits 0-5.
*/
Move case0(FILE* file, int * prevRow, int* prevCol, int* curRow, int* curCol); 

Move case1(FILE* file, int * prevRow, int* prevCol, int* curRow, int* curCol);

Move case2(FILE* file, int * prevRow, int* prevCol, int* curRow, int* curCol);

Move case3(FILE* file, int * prevRow, int* prevCol, int* curRow, int* curCol);

Move getMove(int * prevRow, int* prevCol, int* curRow, int* curCol); // Returns a 'Move' struct with values received and updates prevCol, prevRow

int checkSingleSquare(FILE *file, boardPos start, char **board); // Checks a case where file has a single square

bool checkList(movesList movesLst, movesArray **moves, char **board, boardPos start); // Checks validity of the list 

int logicListLen(movesList lst, boardPos start); // Find size of list without double occurrences 
#endif