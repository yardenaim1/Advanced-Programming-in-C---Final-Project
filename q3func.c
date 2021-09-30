#include "definitions.h"
#include "q3prototype.h"
#include "q2prototype.h"
#include "q1prototype.h"

pathTree findAllPossiblePaths(boardPos  start, movesArray **moves, char **board)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
			moves[i][j].moves = updatedMoves(moves[i][j].moves, j, i, &moves[i][j].size, board); // Delete invalid moves from 'moves' array
	}
	
	pathTree res = findAllPossiblePathsHelper(start, moves, board); // Create the tree
	return res;
}

pathTree findAllPossiblePathsHelper(boardPos  start, movesArray **moves, char **board)
{
	pathTree res;
	treeNode *head = (treeNode*)malloc(sizeof(treeNode));

	head->position[0] = start[0]; head->position[1] = start[1]; // Initialize head node values
	head->next_possible_positions = traverseTree(head, moves, board, start[0]-'A',start[1]-1); // Recursively create the list of the head of the tree, and therefore the tree itself

	res.head = head;
	return res;
}

treeNodeListCell* traverseTree(treeNode *head, movesArray **moves, char **board, int headRow, int headCol)
{
	int curRow, curCol;
	positionToInt(head->position, &curRow, &curCol);
	unsigned int curMoveSize = moves[curRow][curCol].size;

	if (curMoveSize == 0) // Check if there are no moves available 
		return NULL;
	else
	{
	
		bool check = true;
		for (unsigned int i = 0; i < curMoveSize; i++)
		{
			int updRow = moves[curRow][curCol].moves[i].rows + curRow,       // get the location after current move
				updCol = moves[curRow][curCol].moves[i].cols + curCol;
		
			if (board[updRow][updCol] == ' ' && (updRow != headRow || updCol != headCol)) // check if already visited
				check = false;
		}
	
		if (check) // all possible moves from current node are visited
			return NULL;
	}

	treeNodeListCell *headList = NULL; // Will be the head of the list which we return
	treeNodeListCell *curr = (treeNodeListCell*)malloc(sizeof(treeNodeListCell)); // Current list node which goes through the iterations 
	assert(head != NULL && curr != NULL);

	treeNodeListCell *prev = NULL; // To temporarily hold value of previous list node 

	for (unsigned int i = 0; i < curMoveSize; i++) // Check all possible moves from current square
	{
		char **tempBoard = allocateBoard(board); // Create temporary array to update visited squares

		int updRow = moves[curRow][curCol].moves[i].rows + curRow,       // get the location after current move
			updCol = moves[curRow][curCol].moves[i].cols + curCol;

		if (tempBoard[updRow][updCol] == ' ' && (updRow != headRow || updCol != headCol)) // not yet visited and not the values of the head of tree
		{
			curr->node = (treeNode*)malloc(sizeof(treeNode));
			assert(curr->node != NULL);

			tempBoard[updRow][updCol] = '!';
			curr->node->position[0] = updRow + 'A'; curr->node->position[1] = updCol + 1;
			curr->node->next_possible_positions = traverseTree(curr->node, moves, tempBoard, headRow, headCol);
			if (!i)
			{
				headList = curr;
			}
			if (i + 1 == curMoveSize) // Current iteration is last therefore no valid next nodes
			{
				curr->next = NULL;
			}
			else // There are some moves left, so we allocate the next node for the following iteration
			{
				prev = curr;
				treeNodeListCell *next = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
				assert(next != NULL);
				curr->next = next;
				curr = curr->next;
			}
		}
		else // Already visited once
		{
			if (i + 1 == curMoveSize && prev != NULL) // Current node is not a valid one and no more moves left, so the list ends with previous node
			{
				prev->next = NULL;
			}
			
		}
		freeBoard(tempBoard);
	}
	return headList;
}

/* -- Debugging functions -- 

void printTree(pathTree tr)
{
	printTreeHelper(tr.head, 0);
}
void printTreeHelper(treeNode* root, int depth)
{
	for (int i = 0; i < depth; i++)
	{
		printf("    ");
	}
	printf("%c%d->\n", root->position[0], root->position[1]);


	if (root->next_possible_positions == NULL)
		return;
	else
	{
		treeNodeListCell* curr = root->next_possible_positions;
		depth++;
		while (curr != NULL)
		{
			printTreeHelper(curr->node, depth);
			curr = curr->next;
		}
	}
}

void printPossibleMoves(movesArray **moves)
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < M; j++)
		{
			Move *curr = moves[i][j].moves;
			for (size_t k = 0; k < moves[i][j].size; k++)
			{
				printf("%c%d  Row %d - Col %d \n", i + 'A', j + 1, curr[k].rows, curr[k].cols);
			}
		}
	}
}

*/