#include "../HeaderFiles/Validation.h"
#include <stdio.h>
#include <stdbool.h>


bool canBuildMatrix(int matrixSize, int columns, int rows)
{
    if (matrixSize <= columns*rows) {
        return true;
    }
    else{
        return false;
    }
}

bool matrixMultiplication(int matAColumns, int matARows, int matBColumns, int matBRows)
{
    if (matAColumns == matBRows) {
        return true;
    }
    else {
        return false;
    }  
}

