#include "../HeaderFiles/Serial.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>



void runSerial(int rowsA, int colsA, int rowsB, int colsB, double *arrA, double *arrB, FILE *pFile, double *resultSerial){
    struct timeval now, finish; 
    long acum; 
       for (int i = 0; i < 5; i++){
            gettimeofday(&now, 0);
            multiplyMatrixes(rowsA, colsA, rowsB, colsB, arrA, arrB, pFile);
            gettimeofday(&finish, 0);
            long seconds = finish.tv_sec - now.tv_sec;
            long microseconds = finish.tv_usec - now.tv_usec;
            double elapsed = seconds + microseconds*1e-6;
            printf("Time measured: %.9f seconds.\n", elapsed);
            resultSerial[i] = elapsed;
       }
  
    return;
}

void multiplyMatrixes(int rowsA, int colsA, int rowsB, int colsB, double *arrA, double *arrB, FILE *pFile){
    double singleAcum;
	
    //Accede cada linea de la matriz A
    for(int numRowA = 0; numRowA < rowsA; numRowA++){
        //Accede cada columna de la matriz B
       for(int numRowB = 0; numRowB < colsB; numRowB++){
            singleAcum = 0;
            //Accede cada elemento en la linea/columna
            for(int memberNo = 0; memberNo < colsA; memberNo++){
                int elementNoA = numRowA * colsA + memberNo;
                int elementNoB = numRowB * rowsB + memberNo;
                singleAcum += arrA[elementNoA] * arrB[elementNoB];
            }
            printf("Result of [%d, %d] is: %g \n", numRowA, numRowB, singleAcum);
            fprintf(pFile, "%.10g\n", singleAcum);
        }
    }
    return;
}