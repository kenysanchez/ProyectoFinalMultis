#ifndef VALIDATION_DOT_H
#define VALIDATION_DOT_H



#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Validation
{
	bool fileRead, matA, matB;

}; 

bool canBuildMatrix(int matrixSize, int columns, int rows);
bool matrixMultiplication(int matAColumns, int matARows, int matBColumns, int matBRows);


#endif