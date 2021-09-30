#ifndef  Q1PROT_H
#define Q1PROT_H
#include "definitions.h"

/*	The main function of question #1 - receives a 2d array of 'movesArray' moves and a 2d board with asterisks, and updates the array to include valid moves only
*/
boardPosArray** validMoves(movesArray**moves, char **board);

// 'Converts' the moves array to a boardPos array
boardPos* toSqr(Move *moves, int size, int row, int col);

// Returns an updated 'Move' array with valid moves 
Move* updatedMoves(Move* current, int col, int row, int *size, char** board);


/*	-- Debugging functions -- 
	
char** boardInit(); // Initiates the board 


void printMoves(movesArray** moves); // Prints the moves of the array


void printPos(boardPosArray** pos); // prints valid moves in PosArray


Move* movesInit();  // Initiates an array of Moves


movesArray** possibleMoveInit();  // Initiates possible moves in movesArray

*/
#endif 
