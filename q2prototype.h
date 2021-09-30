#ifndef Q2PROT_H
#define Q2PROT_H
#include "definitions.h"

/*	The main function of question #2 - receives a starting position in the board, deletes all invalid moves in the list,
	and prints the board filled with the valid positions according to their order
*/

int display(movesList *moves_list, boardPos start, char **board);

// Convert 'start' indices to int values
void positionToInt(boardPos start, int *row, int *col); 

// Functions to de-allocate the list's memory node by node.
void freeList(movesList *lst);

// Create new nodes, inserts data to the end and node at the end of the doubly X list
moveCell * createNewListNode(Move data, moveCell* next, moveCell* prev);
void insertdataToEndList(movesList *Lst, Move data);
void insertNodeToEndList(movesList *Lst, moveCell*  tail);

// Checks if the lists are empty
bool isEmptyList(movesList *Lst);

// Initialize the lists
void makeEmptyList(movesList *Lst);

// Delete 'toDelete' node from Lst
void deleteNode(movesList *Lst, moveCell *toDelete);

// Creates a copy of 'board'
char** allocateBoard(char **board);

// De-allocates memory of 'board'
void freeBoard(char **board);

// Prints the board
void printBoard(char ** board);
void printRowLine();
void printRowValue(char *line, int lineNum); // receives a line and its number and prints the row with values

/* Debugging functions
void printList(movesList Lst); // Prints the list
movesList createList(); // Create a new list of moves
*/
#endif 