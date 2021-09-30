#ifndef DEFINE_H

#define DEFINE_H
#define _CRT_SECURE_NO_WARNINGS
#define N 5
#define M 5
#define notValidBounds(r, c)  (((r) > (N - 1)) || ((r) < 0) || ((c) > (M - 1)) || ((c) < 0)) ? 1 : 0
#define notValidSquare(boardSqr) ((boardSqr) != ' ') ? 1 : 0

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef char boardPos[2];

typedef struct _move {
	char rows, cols;
} Move;

typedef struct _moveArray {
	unsigned int size;
	Move *moves;
}movesArray;

typedef struct _boardPosArray {
	unsigned int size;
	boardPos *positions;
}boardPosArray;

typedef struct _moveCell {
	Move  move;
	struct _moveCell *next, *prev;
}moveCell;

typedef struct _movesList {
	moveCell* head;
	moveCell* tail;
}movesList;

typedef struct _treeNode treeNode;
typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {
	boardPos position;
	treeNodeListCell *next_possible_positions; 
} treeNode;

typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
}treeNodeListCell;

typedef struct _pathTree {
	treeNode* head;
}pathTree;

typedef unsigned char BYTE;

#endif 