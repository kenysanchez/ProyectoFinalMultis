#ifndef VALIDATION_DOT_H
#define VALIDATION_DOT_H

#include <stdio.h>
#include <stdbool.h>

struct Validation
{
	bool fileRead, matA, matB;

}; 

bool canBuildMatrix(int elementsInFile, int columns, int rows);
bool matrixMultiplication(int matAColumns, int matARows, int matBColumns, int matBRows);


#endif