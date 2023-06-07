#include "../HeaderFiles/Parallel1.h"
#include "omp.h"
#include <sys/time.h>

void runParallel1(int rowsA, int colsA, int rowsB, int colsB, double *arrA, double *arrB, FILE *pFile)
{
    struct timeval now, finish; 
    long acum; 
       for (int i = 0; i < 5; i++){
            gettimeofday(&now, 0);
            #pragma omp parallel num_threads(16)
            {
                parMultiplyMatrixes(rowsA, colsA, rowsB, colsB ,arrA, arrB, pFile);
            }
            gettimeofday(&finish, 0);
            long seconds = finish.tv_sec - now.tv_sec;
            long microseconds = finish.tv_usec - now.tv_usec;
            double elapsed = seconds + microseconds*1e-6;
            printf("Time measured: %.9f seconds.\n", elapsed);
       }
  
    return;
}



void parMultiplyMatrixes(int rowsA, int colsA, int rowsB, int colsB, double *arrA, double *arrB, FILE *pFile)
{
    int amountThreads = omp_get_num_threads();
    int noThread = omp_get_thread_num();
    int remainder = rowsA % omp_get_num_threads();

    
    int interval = rowsA/amountThreads;
    int start = noThread * interval;
    if(noThread + 1 == amountThreads){
        interval += remainder;
    }
    printf("Thread no %d, calculating from %d to %d rows\n", noThread, start, start+interval);
    
    double singleAcum;
    //Accede cada linea de la matriz A
    for(int numRowA = start; numRowA < start + interval; numRowA++){
        //Accede cada columna de la matriz B
       for(int numRowB = 0; numRowB < colsB; numRowB++){
            singleAcum = 0;
            //Accede cada elemento en la linea/columna
            for(int memberNo = 0; memberNo < colsA; memberNo++){
                int elementNoA = numRowA * colsA + memberNo;
                int elementNoB = numRowB * rowsB + memberNo;
                singleAcum += arrA[elementNoA] * arrB[elementNoB];
            }
            //printf("Result of [%d, %d] is: %g \n", numRowA, numRowB, singleAcum);
            #pragma omp atomic
            fprintf(pFile, "%.10g\n", singleAcum);
        }
    }
    return;
}
