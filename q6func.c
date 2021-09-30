#define _CRT_SECURE_NO_WARNINGS
#include "q6prototype.h"
#include "q2prototype.h"
#include "q4prototype.h"

int checkAndDisplayPathFromFile(char *file_name, movesArray **moves, char **board)
{
	FILE *file = fopen(file_name, "rb");
	boardPos start;
	short int size;
	int length = findWantedLength(board), lstLength; // We receive number of valid squares to visit
	bool valid;

	if (file == NULL)
	{
		printf("No such file found!\n");
		return -1;
	}

	fread(&size, sizeof(short int), 1, file);

	if (size < 2) 
	{
		
		if (!size) // No moves in the list, counts as valid but doesn't cover the board
		{
			printf("Moves don't cover the whole board!\n");
			fclose(file);
			return 3;
		}
		else
		{
			
			int singleRes = checkSingleSquare(file, start, board); // There is only one square in the file so we check its validity
			fclose(file);
			return singleRes;
		}
	}

	movesList movesLst = fileToList(file, size, start); // Create list from the file
	fclose(file);

	valid = checkList(movesLst, moves, board, start); // Check if the list contains invalid moves
	if (!valid)
	{
		printf("Non-valid moves in the list!\n");
		freeList(&movesLst);
		return 1;
	}

	display(&movesLst, start, board);
	lstLength = logicListLen(movesLst, start) + 1; // +1 for starting position to be included in actual length the list covers
	freeList(&movesLst);

	if (lstLength == length) // The length of the list covers all valid squares, therefore covers the board
	{
		printf("Moves cover the whole board!\n");
		return 2;
	}
	else
	{
		printf("Moves don't cover the whole board!\n");
		return 3;
	}
}

int checkSingleSquare(FILE *file, boardPos start, char **board)
{
	int row, col;
	
	createStartPos(file, &row, &col, start);

	if (notValidBounds(row, col)) // Check if out of bounds 
	{
		printf("Non-valid move in the list!\n");
		return 1;
	}
	else if (notValidSquare(board[row][col])) // Check if invalid square
	{
		printf("Non-valid move in the list!\n");
		return 1;
	}
	else
	{
		printf("Move doesn't cover the whole board!\n");
		return 3;
	}
}

movesList fileToList(FILE* file, short int size, boardPos start)
{
	movesList lst;
	makeEmptyList(&lst);
	int curCol, curRow, prevCol, prevRow;
	Move currMove;

	createStartPos(file, &prevRow, &prevCol, start); // Initialize first square from file to be starting position and update indices

	for (int i = 1; i < size; i++) 
	{
		switch (i % 4) // There are 4 different cases of extracting data from the file, we handle each one, update indices and append the current 'Move' data to the list
		{
		case 0:
			currMove = case0(file, &prevRow, &prevCol, &curRow, &curCol);
			insertdataToEndList(&lst, currMove);
			break;
		case 1:
			currMove = case1(file, &prevRow, &prevCol, &curRow, &curCol);
			insertdataToEndList(&lst, currMove);
			break;
		case 2:
			currMove = case2(file, &prevRow, &prevCol, &curRow, &curCol);
			insertdataToEndList(&lst, currMove);
			break;
		case 3:
			currMove = case3(file, &prevRow, &prevCol, &curRow, &curCol);
			insertdataToEndList(&lst, currMove);
			break;
		}
	}
	return lst;
}

void createStartPos(FILE* file, int * row, int* col, boardPos start)
{
	BYTE maskStartCol = 0x1c, maskStartRow = 0xe0, curByte;
	long int saver = ftell(file);

	fread(&curByte, sizeof(BYTE), 1, file);
	*row = (curByte & maskStartRow) >> 5;
	*col = (curByte & maskStartCol) >> 2;

	start[0] = (*row) + 'A';
	start[1] = (*col) + 1;
	fseek(file, saver, SEEK_SET);
}

Move getMove(int * prevRow, int* prevCol, int* curRow, int* curCol)
{
	Move curMove;
	curMove.cols = *curCol - *prevCol;
	curMove.rows = *curRow - *prevRow;

	*prevRow = *curRow;
	*prevCol = *curCol;
	return curMove;
}

Move case0(FILE* file, int * prevRow, int* prevCol, int* curRow, int* curCol)
{
	BYTE curByte, case1Col = 0x1c, case1Row = 0xe0;
	long int saver = ftell(file);
	Move curMove;
	fread(&curByte, sizeof(BYTE), 1, file);
	*curRow = (curByte & case1Row) >> 5;
	*curCol = (curByte & case1Col) >> 2;

	curMove = getMove(prevRow, prevCol, curRow, curCol);
	fseek(file, saver, SEEK_SET);
	return curMove;
}

Move case1(FILE* file, int * prevRow, int* prevCol, int* curRow, int* curCol)
{
	BYTE curByte1, case1Col = 0x70, case1Row1 = 0x03, case1Row2 = 0x80, curByte2;
	Move curMove;
	fread(&curByte1, sizeof(BYTE), 1, file);
	long int saver = ftell(file);
	curByte1 = curByte1 & case1Row1;
	fread(&curByte2, sizeof(BYTE), 1, file);
	*curRow = ((curByte2 & case1Row2) >> 7 | (curByte1) << 1);
	curByte2 = (curByte2 & case1Col) >> 4;
	*curCol = curByte2;

	curMove = getMove(prevRow, prevCol, curRow, curCol);
	fseek(file, saver, SEEK_SET);
	return curMove;
}

Move case2(FILE* file, int * prevRow, int* prevCol, int* curRow, int* curCol)
{
	BYTE curByte1, curByte2, case2Col1 = 0x01, case2Col2 = 0xc0, case1Row = 0x0e;
	Move curMove;
	fread(&curByte1, sizeof(BYTE), 1, file);
	long int saver = ftell(file);

	*curRow = (case1Row & curByte1) >> 1;
	curByte1 = (curByte1 & case2Col1) << 2;

	fread(&curByte2, sizeof(BYTE), 1, file);
	curByte2 = (curByte2 & case2Col2) >> 6;
	*curCol = curByte1 | curByte2;

	curMove = getMove(prevRow, prevCol, curRow, curCol);
	fseek(file, saver, SEEK_SET);
	return curMove;
}

Move case3(FILE* file, int * prevRow, int* prevCol, int* curRow, int* curCol)
{
	BYTE curByte1, case3Col = 0x07, case3Row = 0x38;
	Move curMove;
	fread(&curByte1, sizeof(BYTE), 1, file);

	*curRow = (curByte1 & case3Row) >> 3;
	*curCol = curByte1 & case3Col;

	curMove = getMove(prevRow, prevCol, curRow, curCol);
	return curMove;
}

bool checkList(movesList movesLst, movesArray **moves, char **board, boardPos start)
{
	moveCell* head = movesLst.head;
	int row,  col,  curRow, curCol; 
	positionToInt(start, &row, &col); // get starting square indices 
	bool check = true;

	while (head != NULL && check)
	{
		curRow = row + head->move.rows;
		curCol = col + head->move.cols;

		if (notValidBounds(curRow, curCol)) // check if out of bounds
			check = false;

		else if (notValidSquare(board[curRow][curCol])) // check if a non valid square
			check = false;

		row = curRow;
		col = curCol;
		head = head->next;
	}

	return check;

}

int logicListLen(movesList lst, boardPos start)
{
	moveCell *head = lst.head;
	int count = 0, row, col, updRow, updCol;
	positionToInt(start, &row, &col);
	bool checkBoard[N][M];

	for (int i = 0; i < N; i++) // Initialize values 
	{
		for (int j = 0; j < M; j++)
		{
			checkBoard[i][j] = false;
		}
	}

	checkBoard[row][col] = true;  // For starting position

	while (head != NULL)
	{
		updRow = row + head->move.rows;
		updCol = col + head->move.cols;

		if (!(checkBoard[updRow][updCol])) // Move that hasn't already occurred  - increment
			count++;

		checkBoard[updRow][updCol] = true;
		row = updRow; col = updCol;
		head = head->next; 
	}

	return count;
}