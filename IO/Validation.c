#include "../HeaderFiles/Validation.h"
#include <stdio.h>
#include <stdbool.h>

                    // Cantidad de elementos en archivo
bool canBuildMatrix(int elementsInFile, int columns, int rows)
{
    if ((elementsInFile >= columns*rows)) {
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

