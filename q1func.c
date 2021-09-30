#include "definitions.h"
#include "q1prototype.h"

boardPosArray** validMoves(movesArray**moves, char **board)
{
	int i, j;
	boardPosArray** res = (boardPosArray**)malloc(sizeof(boardPos*) * N);
	assert(res != NULL);

	for (i = 0; i < N; i++)
	{
		res[i] = (boardPosArray*)malloc(sizeof(boardPosArray) * M);
		assert(res[i] != NULL);

		for (j = 0; j < M; j++)
		{
			moves[i][j].moves = updatedMoves(moves[i][j].moves, j, i, &moves[i][j].size, board); // Update current 'Move' array and the size of it to include valid moves only
			res[i][j].size = moves[i][j].size;
			res[i][j].positions = toSqr(moves[i][j].moves, res[i][j].size, i, j); // Convert the matching 'Move' array to an array of 'BoardPos'
		}
	}
	return res;
}

Move* updatedMoves(Move* current, int col, int row, int *size, char **board)
{
	int tempSize = *size, logSize = 0, newCol, newRow;
	bool check;
	Move *res = (Move*)malloc(sizeof(Move) * tempSize);
	assert(res != NULL);
	for (int i = 0; i < tempSize; i++)
	{
		newCol = col + current[i].cols;
		newRow = row + current[i].rows;
		if (notValidBounds(newRow, newCol)) // Check if out of bounds or invalid square
			check = false;

		else if (notValidSquare(board[newRow][newCol]))
			check = false;

		else
			check = true;

		if (check) // A valid move, update the array and increment
		{
			res[logSize].cols = current[i].cols;
			res[logSize].rows = current[i].rows;
			logSize++;
		}
	}
	free(current);
	if (!logSize) // No valid moves 
	{
		*size = 0;
		return NULL;
	}
	res = (Move*)realloc(res, sizeof(Move) * logSize);
	assert(res != NULL);

	*size = logSize;
	return res;
}

boardPos* toSqr(Move *moves, int size, int row, int col)
{
	int i;
	boardPos *res = (boardPos*)malloc(sizeof(boardPos)*size);
	assert(res != NULL);
	for (i = 0; i < size; i++) // Boards are with dimensions < 9 so we handle all possible 8 cases for the rows
	{
		switch (moves[i].rows + row)
		{
		case 0: res[i][0] = 'A';
			break;
		case 1: res[i][0] = 'B';
			break;
		case 2: res[i][0] = 'C';
			break;
		case 3: res[i][0] = 'D';
			break;
		case 4: res[i][0] = 'E';
			break;
		case 5: res[i][0] = 'F';
			break;
		case 6: res[i][0] = 'G';
			break;
		case 7: res[i][0] = 'H';
			break;
		}
		res[i][1] = moves[i].cols + col + 1; // Update the col 
	}
	return res;
}

/*	-- Debugging functions -- 

void printMoves(movesArray** moves)
{
	for (int j = 0 ; j < N ; j++)
	{
		printf("Row %d ", j);
		for (int i = 0; i < M; i++)
		{
			printf("Col %d\n", i);
			int size = moves[j][i].size;
			Move* curr = moves[j][i].moves;
			for (int z = 0; z < size; z++)
				printf(" Move #%d: rows - %d cols - %d \n", z, curr[z].rows, curr[z].cols);
		}
	}
}

void printPos(boardPosArray** pos)
{
	int i, j, z;
	for (i = 0; i < N; i++)
	{
		printf("Row %d ", i);
		for (j = 0; j < M; j++)
		{
			printf("Col %d\n", j);
			int size = pos[i][j].size;
			boardPos *curr = pos[i][j].positions;
			for (z = 0; z < size; z++)
				printf(" Move #%d: %c%d\n", z, curr[z][0],curr[z][1]);
		}
	}
}

char** boardInit()
{
	char ** res = (char**)malloc(sizeof(char*) * N);
	assert(res != NULL);
	int i, j;
	for (i = 0; i < N; i++)
	{
		res[i] = (char*)malloc(sizeof(char) * M);
		assert(res[i] != NULL);
	}
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			if (j == 4 || j == 1 || j == 2)
				res[i][j] = ' ';
			else
				res[i][j] = ' ';
		}
	}
	return res;
}

Move* movesInit()
{
	Move* res = (Move*)malloc(sizeof(Move) * N);
	assert(res != NULL);
	for (int i = 0; i < N; i++)
	{
		if (i == 0 || i == 2) // i % 2 == 0 ???
		{
			res[i].cols = i;
			res[i].rows = (i + 1);
		}
		else
		{
			res[i].cols = i - 2;
			res[i].rows = i - 1;
		}
	}
	return res;
}

movesArray** possibleMoveInit()
{
	int i, j;
	movesArray** res = (movesArray**)malloc(sizeof(movesArray*) * N);
	assert(res != NULL);
	for (i = 0; i < N; i++)
	{
		res[i] = (movesArray*)malloc(sizeof(movesArray) * M);
		assert(res[i] != NULL);

		for (j = 0; j < M; j++)
		{
			if (i == 0 && j == 0)
			{
				Move *r = (Move *)malloc(sizeof(Move) * 2);
				r[0].cols = 3;
				r[0].rows = 0;

				r[1].cols = 0;
				r[1].rows = 1;

				res[i][j].moves = r;

				res[i][j].size = (unsigned int)2;
			}
			else if (i == 3 && j == 0)
			{
				Move *r = (Move *)malloc(sizeof(Move));
				r[0].cols = 3;
				r[0].rows = -3;
				res[i][j].moves = r;

				res[i][j].size = 1;
			}
			else
			{
				res[i][j].moves = movesInit();
				res[i][j].size = N;
			}
		}
	}
	return res;
}
*/