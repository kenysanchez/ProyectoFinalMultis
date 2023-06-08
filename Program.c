#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>
#include <immintrin.h>
#include "./HeaderFiles/Matrix.h"
#include "./HeaderFiles/Validation.h"
#include "./HeaderFiles/Parallel1.h"
#include "./HeaderFiles/Parallel2.h"
#include "./HeaderFiles/Serial.h"
#include "./HeaderFiles/Results.h"


int main() {
	struct Matrix matA, matB, matC;
	struct Validation Validation;
	struct Results results;
	struct Serial serial;
	struct Parallel1 parallel1;
	struct Parallel2 parallel2;


	//Initialization----------------------------------------------------------------------------
	printf("Matriz A\n");
	printf("Ingresa la cantidad de columnas de la matriz: \n");
	scanf("%d", &matA.columns);
	printf("Ingresa la cantidad de filas de la matriz: \n");
	scanf("%d", &matA.rows);

	printf("\nMatriz B\n");
	printf("Ingresa la cantidad de columnas de la matriz: \n");
	scanf("%d", &matB.columns);
	printf("Ingresa la cantidad de filas de la matriz: \n");
	scanf("%d", &matB.rows);

	//Reading files-----------------------------------------------------------------------------
    double *matrixA, *matrixB;
    int countA = 0;
    int countB = 0;
    char cA, cB;
    double resultSerial[5];
    double resultParallel1[5];
    double resultParallel2[] = {1,2,3,4,5};
    double averageSerial, averageParallel1, averageParallel2;

    FILE *fileA  = fopen("./Test/matrixA1048576.txt", "r");
    FILE *fileB  = fopen("./Test/matrixB1048576.txt", "r");
    
    //Get file size A
    for (cA = getc(fileA); cA != EOF; cA = getc(fileA))
            if (cA == '\n')
                countA = countA + 1;
    printf("El archivo A tiene %d elementos\n", countA);
    fseek(fileA, 0, SEEK_SET);

    //Memory space validation
    double* arrA = (double*)aligned_alloc(32, countA * sizeof(double));
    if (arrA == NULL) {
        printf("Error: No hay suficiente espacio de memoria\n");
        return 0;
    }
    double* arrTemp = (double*)aligned_alloc(32, countA * sizeof(double));
    if (arrTemp == NULL) {
        printf("Error: No hay suficiente espacio de memoria\n");
        return 0;
    }

    // Store values into array
    float num;
    int n = 0;
    while( fscanf(fileA, "%f", &num) != EOF ) {
        arrA[n++] = num;
    }
    matA.fileRead = true;
    
    //Get file size B
    for (cB = getc(fileB); cB != EOF; cB = getc(fileB)){
        if (cB == '\n'){
            countB = countB + 1;
        }
    }
    printf("El archivo B tiene %d elementos \n", countB);
    fseek(fileB, 0, SEEK_SET);

    //Memory space validation
    double* arrB = (double*)aligned_alloc(32, countB * sizeof(double));
       
    if (arrB == NULL) {
        printf("Error: No hay suficiente espacio de memoria\n");
        return 0;
    }

  // Store values into array
    float numB;
    int m = 0;
    while( fscanf(fileB, "%f", &numB) != EOF ) {
        arrB[m++] = numB;
    }
    matB.fileRead = true;

    //Validation-----------------------------------------------------------------------------------------
    if (canBuildMatrix(countA, matA.columns, matA.rows) && canBuildMatrix(countB, matB.columns, matB.rows)){
        printf("Si se pueden crear las matrices con esos ...\n");
        if (matrixMultiplication(matA.columns, matA.rows, matB.columns, matB.rows)) {
            printf("Si se pueden multiplicar las matrices...\n");
        }
        else {
            printf("Error: No se pueden multiplicar las matrices con esos valores. Intente de nuevo\n");
            return 0;
        }
    }
    else {
        printf("Error: No se pueden construir las matrices con esos valores. Intente de nuevo\n");
        return 0;
    }

    //Transpose Mat C
    transposeArray (arrA, arrTemp, matA.columns, matA.rows);

    //Create C file
    FILE *fileC;
    fileC = fopen("matrixC.txt", "w");

	//Serial--------------------------------------------------------------------------------------------

    struct timeval now, finish; 
    printf("Testing serial\n");
    gettimeofday(&now, 0);
    runSerial(matA.rows, matA.columns,  matB.rows, matB.columns, arrA, arrB, fileC, resultSerial);
    gettimeofday(&finish, 0);
    long seconds = finish.tv_sec - now.tv_sec;
    long microseconds = finish.tv_usec - now.tv_usec;
    double elapsed = seconds + microseconds*1e-6;
    averageSerial = getAverage(resultSerial);

    printf("Avg time measured: %.9f seconds.\n", averageSerial);
    printf("Finished serial\n");


	//Parallel 1 ---------------------------------------------------------------------------------------

    printf("Testing parallel with OMP\n");
    gettimeofday(&now, 0);
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        runParallel1(matA.rows, matA.columns,  matB.rows, matB.columns, arrA, arrB, fileC, resultParallel1);
    }
    gettimeofday(&finish, 0);
    seconds = finish.tv_sec - now.tv_sec;
    microseconds = finish.tv_usec - now.tv_usec;
    elapsed = seconds + microseconds*1e-6;
    averageParallel1 = getAverage(resultParallel1);

    printf("Avg time measured: %.9f seconds.\n", averageParallel1);
    printf("Finished parallel\n");
	
    //Parallel 2 ---------------------------------------------------------------------------------------
  
    //TODO: Quitar para pruebas
    averageParallel2= 0.0;

	//Results ------------------------------------------------------------------------------------------
	printResultsAreTheSame();
	printResultsTable(resultSerial, resultParallel1, resultParallel2, averageSerial, averageParallel1, averageParallel2);
	printBestMethod(averageSerial, averageParallel1, averageParallel2);

    fclose(fileA);
    fclose(fileB);
    fclose(fileC);

	return 0;
}