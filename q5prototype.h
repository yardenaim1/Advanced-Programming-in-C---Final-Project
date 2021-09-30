#ifndef  Q5PROT_H
#define Q5PROT_H
#define _CRT_SECURE_NO_WARNINGS
#include "definitions.h"

/*	The main function of question #5 -  creates a matching binary file out of 'pos_array' with the wanted representation of the board's squares as bits 
*/
void saveListToBinFile(char *file_name, boardPosArray *pos_arr); 

BYTE* arrToBits(boardPosArray *pos_arr, short int size, int *bitArrSize); // Creates an array by converting the elements in pos_arr into matching bits

void updateBits(BYTE* bitArr, int *byteNum, BYTE curr, int *shiftCount); // Updates the bits in 'bitArr' according to specific cases

#endif 
