#include "../HeaderFiles/Parallel1.h"
#include "omp.h"
#include <sys/time.h>
#include <immintrin.h>

void runParallel1(int rowsA, int colsA, int rowsB, int colsB, double *arrA, double *arrB, FILE *pFile)
{
    struct timeval now, finish; 
    long acum; 
       for (int i = 0; i < 5; i++){
            gettimeofday(&now, 0);
            #pragma omp parallel num_threads(4)
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
    __m256d a, b;
    double *resultArray = NULL;
    resultArray = (float*)aligned_alloc(32, sizeof(double) * 4);



    if(noThread + 1 == amountThreads){
        interval += remainder;
    }
    //printf("Thread no %d, calculating from %d to %d rows\n", noThread, start, start+interval);
    
    double singleAcum;
    //Accede cada linea de la matriz A
    for(int numRowA = start; numRowA < start + interval; numRowA++){

        //Accede cada columna de la matriz B
       for(int numRowB = 0; numRowB < colsB; numRowB++){
            singleAcum = 0;

            //Accede cada elemento en la linea/columna
            for(int memberNo = 0; memberNo < colsA; memberNo+=4){

                //Obtains the element number in the matrix A
                int elementNoA = numRowA * colsA + memberNo;
                //Obtains the element number in the matrix B
                int elementNoB = numRowB * rowsB + memberNo;
                //Loads the next 8 double elements
                
                //printf("Loading\n");
                a = _mm256_load_pd(&arrA[elementNoA]);
                b = _mm256_load_pd(&arrB[elementNoB]);
                //printf("StoppedLoading\n");
                //printf("what\n");
                //printf("numRowA %d, numRowB %d, memberNo %d\n", numRowA, numRowB, memberNo);
                //printf("thefuck\n");
                int elementsRemainder = 4;
                //This is true if it is the last loop
                if(memberNo + 4 >= colsA){

                   elementsRemainder = colsA % 4;

                }

                //Multiplies the 8 double elements and stores it in c
                _mm256_store_pd(&resultArray[0], _mm256_mul_pd(a, b)); 
                //printf("stored result\n");
                for(int x=0; x<elementsRemainder; x++){
                    //printf("ADDING ELEMENT %d", x);
                    singleAcum += resultArray[x];
                }
            }
            //printf("Result of [%d, %d] is: %g \n", numRowA, numRowB, singleAcum);
            
            //TODO: Change so instead of directly writing results to file, it writes results
            //to a double pointer, then it writes to file
            fprintf(pFile, "%.10g\n", singleAcum);
        }
    }
    return;
}
