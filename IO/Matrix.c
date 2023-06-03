#include "../HeaderFiles/Matrix.h"
#include <stdio.h>
#include <stdbool.h>

void transposeArray (double *entryMat, double *exitMat, int cols, int rows){

    double *pointerAux, *pointerExit;
    pointerAux = entryMat;
    pointerExit = exitMat;
  
{
        
        for(int i = 0; i < cols; i++)
            {
                for(int j = 0; j < rows; j++)
                {
                    pointerAux = entryMat + (i+(j*cols));
                    *pointerExit = *pointerAux;
                    pointerExit += 1;
                }
            }
    return;
}


