#include "q5prototype.h"

void saveListToBinFile(char *file_name, boardPosArray *pos_arr)
{
	FILE *file;
	short int size = (short int)pos_arr->size;
	int bitArrSize;
	//boardPos arr[SIZE] = { {'C',5},{'A',4},{'B',3},{'D',1},{'E',3} , {'C',5},{'B',3},{'E',3 } }; // Temporary struct similar to question desc.
	BYTE *bitsArray = arrToBits(pos_arr, size, &bitArrSize); // Create correct the binary representation of 'pos_arr'

	/*  -- Prints the bits -- 
	for (int j = 0; j < bitArrSize; j++)
	{	
		for (int i = 0; i < 8; i++)
		{
			printf("%d", ((bitsArray[j] & (1 << (7 - i % 8))) >> (7 - i % 8)));
			if (i % 7 == 0 && i != 0)
				printf(" ");
		}
		
	} */
	file = fopen(file_name, "wb");
	assert(file != NULL);

	fwrite(size, sizeof(short int), 1, file);
	fwrite(bitsArray, sizeof(BYTE), bitArrSize, file);

	free(bitsArray);
	fclose(file);
}

BYTE* arrToBits(boardPosArray *pos_arr, short int size, int *bitArrSize)
{
	int byteSize = ((size * 2) / 3) + 1; // required number of bytes
	*bitArrSize = byteSize;
	BYTE  curr;
	int byteNum = 0, posIndex = 0, rowOrCol = 0, shiftCount = 5; // For the first bit to be in its place starting shift (to the left) is 5

	BYTE *bitsArray = (BYTE*)calloc(byteSize, sizeof(BYTE)); 
	assert(bitsArray != NULL);

	for (int i = 0; i < size * 2; i ++) // size * 2 iterations because every element in 'pos_arr' will need its own iteration
	{
		if (!rowOrCol) // Extract the row bits
		{
			curr = pos_arr->positions[posIndex][rowOrCol] - 'A';
			rowOrCol = 1;
		}
		else // Extract the column bits and increment posIndex to get the next square in next iteration
		{
			curr = pos_arr->positions[posIndex][rowOrCol] - 1;
			rowOrCol = 0;
			posIndex++;

		}

		if (shiftCount < 0) // The bits which we need to insert into 'bitsArray' are spread across two bytes
		{
			
			updateBits(bitsArray, &byteNum, curr, &shiftCount);
		}
		else // No special case so update the current byte with the bits shifted to matching position and update shiftCount
		{
			bitsArray[byteNum] = bitsArray[byteNum] | (curr << shiftCount);
			shiftCount -= 3;
		}
	}
	return bitsArray;
}

void updateBits(BYTE* bitArr, int *byteNum, BYTE curr, int *shiftCount)
{
	BYTE mask1 = 1, mask3 = 0x03, mask4 = 0x04   // The masks we need to handle all cases
		,mask6 = 0x06, mask7 = 0x07;

	(*byteNum)++;   // Current bits are 'between' two bytes so increment to get accurate index

	switch ((*byteNum) % 3) // There are 3 different ways to handle bits update
	{
	case 0: bitArr[*byteNum] = bitArr[*byteNum] | (curr << 5); // Regular case - all the bits in one byte
			*shiftCount = 2;
		break;

	case 1: *shiftCount = 4;     // Two left bits in previous byte and the least significant bit in the current byte
			bitArr[(*byteNum) - 1] = bitArr[(*byteNum) - 1] | ((curr & mask6) >> 1);
			bitArr[*byteNum] = bitArr[*byteNum] | ((curr & mask1) << 7);
		break;

	case 2: *shiftCount = 3; // Left bit in previous byte and two others in current byte
			bitArr[(*byteNum) - 1] = bitArr[(*byteNum) - 1] | ((curr & mask4) >> 2);
			bitArr[*byteNum] = bitArr[*byteNum] | ((curr & mask3) << 6);
		break;
	}
}