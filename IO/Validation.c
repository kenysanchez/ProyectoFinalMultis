#include "../HeaderFiles/Validation.h"
#include <stdio.h>
#include <stdbool.h>

                    // Cantidad de elementos en archivo
bool canBuildMatrix(int matrixSize, int columns, int rows)
{
    int matrixElements = columns*rows;
    if ((matrixSize <= columns*rows)&&(matrixElements<=matrixSize)) {
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

