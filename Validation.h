#include <stdio.h>
#include <stdbool.h>

struct Validation
{
	bool fileRead, matA, matB;

}; 


void readFile();
bool canBuildMatrix(int matrixSize);
bool matrixMultiplication(bool matA, bool matB);
bool enoughMemorySpace(int memorySpace);
