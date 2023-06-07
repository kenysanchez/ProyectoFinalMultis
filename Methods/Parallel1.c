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
    __m512d a, b, c;


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
            for(int memberNo = 0; memberNo < colsA; memberNo+=8){

                //Obtains the element number in the matrix A
                int elementNoA = numRowA * colsA + memberNo;
                //Obtains the element number in the matrix B
                int elementNoB = numRowB * rowsB + memberNo;
                //Loads the next 8 double elements
                a = _mm512_load_pd(&arrA[elementNoA]);
                b = _mm512_load_pd(&arrB[elementNoB]);

                //Initializes all bits in 8 bit mask to 1
                char mask = 255;

                //This is true if it is the last loop
                if(memberNo + 8 >= colsA){
                    //When it is the last loop, it means not all elements must be multiplied
                    //So we use the remainder to obtain how much elements are left to multiply
                    //Then we use the mask in the function to only multiply those elements
                    int elementsRemainder = colsA % 8;

                    mask = mask << (8 - elementsRemainder);

                    //I.E. If we have 7 elements, then the code will enter this last loop
                    //7 % 8 is 7
                    //Our mask is 1111 1111
                    //The mask will be shifted 8 - 7 = 1
                    //So the mask in the end will be 1111 1110


                }

                //Multiplies the 8 double elements and stores it in c
                _mm512_store_pd(&c, _mm512_maskz_mul_pd(mask, a, b)); 

                //Sums the elements in C and adds it to 'singleAcum'
                singleAcum += _mm512_mask_reduce_add_pd(mask, c);
            }
            //printf("Result of [%d, %d] is: %g \n", numRowA, numRowB, singleAcum);
            
            //TODO: Change so instead of directly writing results to file, it writes results
            //to a double pointer, then it writes to file
            fprintf(pFile, "%.10g\n", singleAcum);
        }
    }
    return;
}

