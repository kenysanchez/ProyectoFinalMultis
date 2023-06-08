#include "../HeaderFiles/Parallel2.h"
#include <sys/time.h>
#include <cuda.h>



__global__ void parMultiplyMatrixesCuda(int rowsA, int colsA, int rowsB, int colsB, double *arrA, double *arrB, double * arrC)
{
    double singleAcum;

            for(int memberNo = 0; memberNo < colsA; memberNo++){
                int elementNoA = blockIdx.x * colsA + memberNo;
                int elementNoB = threadIdx.x * rowsB + memberNo;
                singleAcum += arrA[elementNoA] * arrB[elementNoB];
            }
            arrC[blockIdx.x*colsB + threadIdx.x] = singleAcum;
    return;
}



extern "C" void runParallel2(int rowsA, int colsA, int rowsB, int colsB, double *arrA, double *arrB, double *arrC)
{   
    int blockSize = rowsA;
    int amountThreads = colsB;

    double * d_arrA;
    double * d_arrB;
    double * d_arrC;

    cudaMalloc((void**)& d_arrA, rowsA * colsA * sizeof(double));
    cudaMalloc((void**)& d_arrB, rowsB * colsB * sizeof(double));
    cudaMalloc((void**)& d_arrC, rowsA * colsB * sizeof(double));

    cudaMemcpy(d_arrA, arrA, rowsA * colsA * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_arrB, arrB, rowsB * colsB * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_arrC, arrC, rowsA * colsB * sizeof(double), cudaMemcpyHostToDevice);


    struct timeval now, finish; 
    //long acum; 
       for (int i = 0; i < 5; i++){
            gettimeofday(&now, 0);
                
            //printf("Calling %d blocks and %d threads\n", blockSize, amountThreads);

            parMultiplyMatrixesCuda<<<blockSize, amountThreads>>>(rowsA, colsA, rowsB, colsB , d_arrA, d_arrB, d_arrC);
            cudaDeviceSynchronize();
            gettimeofday(&finish, 0);
            long seconds = finish.tv_sec - now.tv_sec;
            long microseconds = finish.tv_usec - now.tv_usec;
            double elapsed = seconds + microseconds*1e-6;
            printf("Time measured: %.9f seconds.\n", elapsed);
            cudaError_t error = cudaGetLastError();
       }

    cudaMemcpy(arrA, d_arrA, rowsA * colsA * sizeof(double), cudaMemcpyDeviceToHost);
    cudaMemcpy(arrB, d_arrB, rowsA * colsA * sizeof(double), cudaMemcpyDeviceToHost);
    cudaMemcpy(arrC, d_arrC, rowsA * colsB * sizeof(double), cudaMemcpyDeviceToHost);

    cudaError_t error = cudaGetLastError();
    if (error != cudaSuccess)
    {
        printf("Cuda error: %s\n", cudaGetErrorString(error));
    }
  
    return;
}



