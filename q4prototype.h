#ifndef  Q4PROT_H
#define Q4PROT_H
#include "definitions.h"

/*	The main function of question #4 - receives a starting square, possible moves array and a board with asterisks. 
	Using the helping recursive function, it will create a list of a possible path of moves that covers the whole board. If none found, returns NULL value.
*/
movesList *findPathCoveringAllBoard(boardPos start, movesArray **moves, char **board);

// Recursive function which constructs the list with a path that covers the board. Returns NULL if not found such a path.
movesList* findPathCoveringAllBoardHelper(treeNode* curr, treeNode * prev, int pathLength, int currPath, movesArray **moves);

// Returns the length of the list
int listLength(moveCell *head);

// Returns the number of valid squares in the board to visit
int findWantedLength(char** board);

// De-allocate memory of tree
void freeTree(pathTree tree);

void freeTreeHelper(treeNode *head);

#endif 