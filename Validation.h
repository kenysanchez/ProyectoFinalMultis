#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Validation
{
	bool fileRead, matA, matB;

}; 


void readFile(int columns, int rows);
bool canBuildMatrix(int matrixSize);
bool matrixMultiplication(bool matA, bool matB);
bool enoughMemorySpace(int memorySpace);
