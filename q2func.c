#include "definitions.h"
#include "q2prototype.h"
#include "q3prototype.h"

int display(movesList *moves_list, boardPos start, char **board)
{
	char **currBoard = allocateBoard(board); // Creates a temporary board to work with
	int moveNum = 1, deleteNum = 0, currRow, currCol, tempR,tempC; 
	positionToInt(start, &currRow, &currCol); // Get the first square indices
	currBoard[currRow][currCol] = '#'; // Update starting position with '#'
	bool check;
	moveCell *currMove = moves_list->head;

	while (currMove != NULL)
	{
		tempR = currRow; tempC = currCol; // Update indices to reflect current square and then get the next square's indices from the list
		currRow += currMove->move.rows;
		currCol += currMove->move.cols;

		if (notValidBounds(currRow, currCol)) // check if out of bounds
			check = false;
		else if (notValidSquare(currBoard[currRow][currCol])) // check for a valid square 
			check = false;
		else
			check = true;

		if (check) // Current move is valid, place the current move number in the square
		{
			currBoard[currRow][currCol] = moveNum + '0'; // int to char
			moveNum++;
			currMove = currMove->next;
		}
		else // Not a valid move, delete current move from the list and increment the counter
		{
			currRow = tempR; currCol = tempC;
			moveCell *temp = currMove;
			currMove = currMove->next;
			deleteNode(moves_list, temp);
			deleteNum++;
		}

	}
	
	printBoard(currBoard); 
	freeBoard(currBoard);
	return deleteNum;
}

void makeEmptyList(movesList *Lst)
{
	Lst->head = NULL;
	Lst->tail = NULL;
}

moveCell *createNewListNode(Move data, moveCell* next, moveCell* prev)
{
	moveCell* res;
	res = (moveCell*)malloc(sizeof(moveCell));
	assert(res != NULL);
	res->move = data;
	res->next = next;
	res->prev = prev;
	return res;
}

void insertdataToEndList(movesList *Lst, Move data)
{
	moveCell *newTail;
	newTail = createNewListNode(data, Lst->tail, NULL);
	insertNodeToEndList(Lst, newTail);
}

void insertNodeToEndList(movesList *Lst, moveCell*  tail)
{
	if (isEmptyList(Lst))
		Lst->head = Lst->tail = tail;
	else
	{
		Lst->tail->next = tail;
		tail->prev = Lst->tail;
		Lst->tail = tail;
	}
	tail->next = NULL;
}

bool isEmptyList(movesList *Lst)
{
	if (Lst->head == NULL)
		return true;
	else
		return false;
}

void freeList(movesList *lst)
{
	moveCell *p, *q;
	if (isEmptyList(lst))
		return;
	p = lst->head;
	while (p->next != NULL)
	{
		q = p;
		p = p->next;
		free(q);
	}
	free(p);
}

void deleteNode(movesList *Lst, moveCell *toDelete)
{
	if (toDelete == Lst->head && toDelete == Lst->tail) // toDelete is the only node so we'll have an empty list
	{
		Lst->head = Lst->tail = NULL;
	}
	else if (toDelete == Lst->head)
	{
		Lst->head = toDelete->next;
		toDelete->next->prev = NULL;
	}
	else if (toDelete == Lst->tail)
	{
		Lst->tail = toDelete->prev;
		toDelete->prev->next = NULL;
	}
	else // toDelete is neither a head or tail of the list
	{
		moveCell *prev = toDelete->prev, *next = toDelete->next;
		prev->next = next;
		next->prev = prev;
	}
	free(toDelete);
}

char** allocateBoard(char **board)
{
	char **tempBoard = (char**)malloc(sizeof(char*) * N);
	assert(tempBoard != NULL);

	for (int i = 0; i < N; i++)
	{
		tempBoard[i] = (char*)malloc(sizeof(char) * M);
		for (int j = 0; j < M; j++)
			tempBoard[i][j] = board[i][j];
	}
	return tempBoard;
}

void freeBoard(char **board)
{
	for (int i = 0; i < N; i++)
	{
		free(board[i]);
	}
	free(board);
}

void printBoard(char **board)
{
	int rowN = 3;
	printf("\n");
	for (int i = 0; i < (N * 2) + 3; i++) // According to how the board is built, the correct number of iterations is (rows * 2) + 3
	{
		if (i == 1) // Second iteration - print the column numbers
		{
			for (int j = 0; j < M + 1; j++)
			{
				printf("|  ");
				if (j != 0)
					printf("%d  ", j);
				else
					printf(" ");
			}
			printf("|\n");
		}
		else if (i % 2 == 0) // Every even row is a 'border'
			printRowLine();
		else // Odd rows are where the values of the board are printed
		{
			printRowValue(board[i - rowN], i - rowN);
			rowN++;
		}
	}
}

void printRowLine()
{
	for (int i = 0; i < M + 1; i++)
	{
		if (i == 0)
			printf("+---+");
		else
			printf("-----+");
	}
	printf("\n");
}

void printRowValue(char *line, int lineNum)
{
	int j = 0;
	for (int i = 0; i < M + 1 ; i++)
	{
		printf("| ");
		if (i == 0)
			printf("%c ", lineNum + 'A');
		else
		{
			printf(" %c  ", line[j]);
			j++;
		}
	}
	printf("|\n");
}

void positionToInt(boardPos start, int *row, int *col)
{
	*row = start[0] - 'A';
	*col = start[1] - 1;
}

/*  --Debugging functions-- 

movesList createList()
{
	movesList res; makeEmptyList(&res);
	Move curr;
	for (int i = 0; i < 10; i++)
	{
		switch (i)
		{
		case 0: curr.cols = 2; curr.rows = 0;
			break;
		case 1: curr.cols = -3; curr.rows = 0;
			break;
		case 2: curr.cols = -2; curr.rows = 2;
			break;
		case 3: curr.cols = 1; curr.rows = 0;
			break;
		case 4: curr.cols = 1; curr.rows = 3;
			break;
		case 5: curr.cols = 0; curr.rows = -2;
			break;
		case 6: curr.cols = -1; curr.rows = -1;
			break;
		case 7: curr.cols = 2; curr.rows = -2;
			break;
		case 8: curr.cols = 1; curr.rows = 2;
			break;
		case 9: curr.cols = -2; curr.rows = 1;
			break;
		}
		insertdataToEndList(&res, curr);
	}
	return res;
}

void printList(movesList Lst)
{
	moveCell *curr = Lst.head;
	moveCell *tail = Lst.tail;
	while (curr != NULL)
	{
		printf("(%d , %d)->", curr->move.rows, curr->move.cols);
		curr = curr->next;
	}
} */