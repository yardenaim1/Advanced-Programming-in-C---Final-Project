#ifndef  Q3PROT_H
#define Q3PROT_H

#include "definitions.h"

/*	The main function of question #3 - receives a starting position, all possible moves array and a board with asterisks. 
	Firstly, updates the possible moves array to include valid moves only. Afterwards, using the helping function, creates a 'pathTree' struct that represents all possible moves.
*/
pathTree findAllPossiblePaths(boardPos  start, movesArray **moves, char **board); 

pathTree findAllPossiblePathsHelper(boardPos  start, movesArray **moves, char **board); // Initializes head of tree and calls the recursive function below

treeNodeListCell* traverseTree(treeNode *head, movesArray **moves, char **board, int headRow, int headCol); // Recursive function which creates the wanted tree by creating nodes, their relevant lists of next positions and match between them

/*	-- Debugging functions --   
void printTree(pathTree tr);
void printTreeHelper(treeNode* root, int depth);
void printPossibleMoves(movesArray **moves);
*/
#endif
