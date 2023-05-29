#include <stdio.h>
#include <stdbool.h>

struct MatrixValidation
{
	bool fileRead, matA, matB;

} MatrixValidation; 


void readFile();
bool canBuildMatrix(int matrixSize);
bool matrixMultiplication(bool matA, bool matB);
bool enoughMemorySpace(int memorySpace);
