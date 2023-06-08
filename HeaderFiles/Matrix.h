#ifndef MATRIX_DOT_H
#define MATRIX_DOT_H

#include <stdio.h>
#include <stdbool.h>

struct Matrix
{
	int rows, columns;
	bool fileRead, isValid;
};

void transposeArray(double *entryMat, double *exitMat, int cols, int rows);

int calculateMatrixCsize(int colsA, int rowsB);

#endif
