#include "q4prototype.h"
#include "q3prototype.h"
#include "q2prototype.h"
#include "q1prototype.h"

movesList *findPathCoveringAllBoard(boardPos start, movesArray **moves, char **board)
{
	pathTree tree = findAllPossiblePaths(start, moves, board); // get all possible paths into tree
	
	int pathLength = findWantedLength(board); // get required path length

	movesList *res = findPathCoveringAllBoardHelper(tree.head->next_possible_positions->node, tree.head, pathLength, 1, moves);
	return res;
}

movesList* findPathCoveringAllBoardHelper(treeNode* curr, treeNode * prev, int pathLength, int currPath, movesArray **moves)
{
	int curRow, curCol, prevRow, prevCol;
	positionToInt(curr->position, &curRow, &curCol); // Get current node's indices
	positionToInt(prev->position, &prevRow, &prevCol); // Get previous node's indices
	int moveSize = moves[prevRow][prevCol].size;

	if (curr->next_possible_positions == NULL) 
	{
		if (pathLength - 1 == currPath) // Found a last node which has the length needed to cover all board
		{
			Move curMove = { curRow - prevRow, curCol - prevCol }; // Initiate relevant move struct
			movesList *lstEnd = (movesList*)malloc(sizeof(movesList));
			assert(lstEnd != NULL);
			makeEmptyList(lstEnd);
			insertdataToEndList(lstEnd, curMove);
			return lstEnd;
		}
		else // Last node in a path but doesn't cover the whole board
			return NULL;
	}
	else
	{
		treeNodeListCell * currTreeLst = prev->next_possible_positions;
		for (int i = 0; i < moveSize; i++)
		{
			if (currTreeLst != NULL && currTreeLst->node->next_possible_positions != NULL) // There is a possible path  from current node 
			{
				// Recursive call to get path from current node (square)
				movesList *curLst = findPathCoveringAllBoardHelper(currTreeLst->node->next_possible_positions->node, currTreeLst->node, pathLength, currPath + 1, moves);

				if (curLst != NULL) // There is a possible list from current square so we check if it's a useful one
				{
					int lstPosRow = currTreeLst->node->position[0] - prev->position[0], lstPosCol = currTreeLst->node->position[1] - prev->position[1];
					Move move = { lstPosRow, lstPosCol };
					moveCell* cell = createNewListNode(move, curLst->head, NULL);
					curLst->head->prev = cell;
					curLst->head = cell;

					if (listLength(curLst->head) == pathLength - currPath) // Check if the length of the list answers our queries
						return curLst;
					else // The list is not as long as it should be, de-allocate it and check next node (square)
					{
						free(curLst);
						currTreeLst = currTreeLst->next;
					}
				}
				else // No possible list, move forward to next square in current level
					currTreeLst = currTreeLst->next;
			}
			else if (currTreeLst != NULL) // There were no path from the square, if it's not the end of the list then we paths from the next square
				currTreeLst = currTreeLst->next;
		}
		return NULL;
	}
}

int listLength(moveCell *head)
{
	moveCell *curr = head;
	int count = 0;
	while (curr != NULL)
	{
		count++;
		curr = curr->next;
	}
	return count;
}

int findWantedLength(char** board)
{
	int wanted;
	int numOfAsterisk = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			if (board[i][j] == '*')
				numOfAsterisk++;
	}
	wanted = (N * M) - numOfAsterisk;
	return wanted;
}

void freeTree(pathTree tree)
{
	freeTreeHelper(tree.head);
}

void freeTreeHelper(treeNode *head)
{
	if (head->next_possible_positions == NULL)
	{
		free(head);
		head = NULL;
		return;
	}

	else
	{
		
		treeNodeListCell *headLst = head->next_possible_positions;
		treeNodeListCell *temp;
		while (headLst->next != NULL)
		{
			freeTreeHelper(headLst->node);
			temp = headLst;
			headLst = headLst->next;
			free(temp);
			temp = NULL;
		}
		
		free(headLst);
		free(head);
		
	}
}