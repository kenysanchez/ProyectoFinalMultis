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
    printf("Ingresa la cantidad de filas de la matriz: \n");
	scanf("%d", &matA.rows);
	printf("Ingresa la cantidad de columnas de la matriz: \n");
	scanf("%d", &matA.columns);


	printf("\nMatriz B\n");
    printf("Ingresa la cantidad de filas de la matriz: \n");
	scanf("%d", &matB.rows);
	printf("Ingresa la cantidad de columnas de la matriz: \n");
	scanf("%d", &matB.columns);


	//Reading files-----------------------------------------------------------------------------
    double *matrixA, *matrixB;
    int countA = 0;
    int countB = 0;
    char cA, cB;
    double resultSerial[5];
    double resultParallel1[5];
    double resultParallel2[5];
    double averageSerial, averageParallel1, averageParallel2;

    FILE *fileA  = fopen("matrizA.txt", "r");
    FILE *fileB  = fopen("matrizB.txt", "r");
    
    //FILE *fileA  = fopen("./Test/matrixA1048576.txt", "r");
    //FILE *fileB  = fopen("./Test/matrixB1048576.txt", "r");

    
    
    //Get file size A
    for (cA = getc(fileA); cA != EOF; cA = getc(fileA))
            if (cA == '\n')
                countA = countA + 1;
    printf("El archivo A tiene %d elementos\n", countA);
    fseek(fileA, 0, SEEK_SET);

    //Memory space validation
    double* h_arrA = (double*)malloc(countA * sizeof(double));
    if (h_arrA == NULL) {
        printf("Error: No hay suficiente espacio de memoria\n");
        return 0;
    }


    // Store values into host arra
    float num;
    int n = 0;
    while( fscanf(fileA, "%f", &num) != EOF ) {
        h_arrA[n++] = num;
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
    double* h_arrB = (double*)malloc(countB * sizeof(double));
       
    if (h_arrB == NULL) {
        printf("Error: No hay suficiente espacio de memoria\n");
        return 0;
    }

    double* h_arrBTrans = (double*)malloc(countB * sizeof(double));
    if (h_arrBTrans == NULL) {
        printf("Error: No hay suficiente espacio de memoria\n");
        return 0;
    }

    

  // Store values into host array
    float numB;
    int m = 0;
    while( fscanf(fileB, "%f", &numB) != EOF ) {
        h_arrB[m++] = numB;
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



    //PRINT
    printf("BEFORE MAT B\n");
    for (int i = 0; i < 20; i++) {
        printf("%.12f\n", h_arrB[i]);
    }

    transposeArray(h_arrB, h_arrBTrans, matB.columns, matB.rows);

    

    printf("AFTER MAT B\n");
    for (int i = 0; i < 20; i++) {
        printf("%.12f\n", h_arrBTrans[i]);
    }

    // //Creation of the result
    // int matCSize = calculateMatrixCsize(matA.columns, matB.rows);
    
    // //Memory space validation
    // double* d_arrC = (double*)malloc(matCSize * sizeof(double));
       
    // if (d_arrC == NULL) {
    //     printf("Error: No hay suficiente espacio de memoria\n");
    //     return 0;
    // }

    int countC = matA.rows * matB.columns;
    double* h_arrC = malloc(countC * sizeof(double));
    


    //Create C file
    FILE *fileC, *fileCParOne, *fileCParTwo;
    fileC = fopen("matrixCSer.txt", "w");
    fileCParOne = fopen("matrixCParOne.txt", "w");
    fileCParTwo = fopen("matrixCParTwo.txt", "w");


    //Close first files that were read    
    fclose(fileA);
    fclose(fileB);




	//Serial--------------------------------------------------------------------------------------------


    struct timeval now, finish; 
    printf("Testing serial\n");
    gettimeofday(&now, 0);
    runSerial(matA.rows, matA.columns,  matB.rows, matB.columns, h_arrA, h_arrBTrans, h_arrC, resultSerial);
    gettimeofday(&finish, 0);
    long seconds = finish.tv_sec - now.tv_sec;
    long microseconds = finish.tv_usec - now.tv_usec;
    double elapsed = seconds + microseconds*1e-6;
    averageSerial = getAverage(resultSerial);
    
    printf("Avg time measured: %.9f seconds.\n", averageSerial);
    printf("Finished serial\n");

    //Closing of FileC Serial
    
    printf("Writing result to file...\n");
    for(int x = 0; x < matA.rows * matB.columns; x++){
        fprintf(fileC, "%.10g\n", h_arrC[x]);
    }
    fclose(fileC);

	//Parallel 1 ---------------------------------------------------------------------------------------

    printf("Testing parallel with OMP\n");
    gettimeofday(&now, 0);
    omp_set_num_threads(4);
    runParallel1(matA.rows, matA.columns,  matB.rows, matB.columns, h_arrA, h_arrBTrans, h_arrC, resultParallel1);
    gettimeofday(&finish, 0);
    seconds = finish.tv_sec - now.tv_sec;
    microseconds = finish.tv_usec - now.tv_usec;
    elapsed = seconds + microseconds*1e-6;
    averageParallel1 = getAverage(resultParallel1); 

    printf("Avg time measured: %.9f seconds.\n", averageParallel1);
    printf("Finished parallel\n");

    printf("Writing result to file...\n");
    for(int x = 0; x < matA.rows * matB.columns; x++){
        fprintf(fileCParOne, "%.10g\n", h_arrC[x]);
    }
    fclose(fileCParOne);
	
    //Parallel 2 ---------------------------------------------------------------------------------------

    printf("Testing parallel with CUDA\n");
    gettimeofday(&now, 0);

    runParallel2(matA.rows, matA.columns,  matB.rows, matB.columns, h_arrA, h_arrBTrans, h_arrC, resultParallel2);

    gettimeofday(&finish, 0);
    seconds = finish.tv_sec - now.tv_sec;
    microseconds = finish.tv_usec - now.tv_usec;
    elapsed = seconds + microseconds*1e-6;
    averageParallel2 = getAverage(resultParallel2);

    printf("Avg time measured: %.9f seconds.\n", averageParallel2);
    printf("Finished parallel with CUDA\n");

    printf("Writing result to file...\n");
        for(int x = 0; x < matA.rows * matB.columns; x++){
        fprintf(fileCParTwo, "%.10g\n", h_arrC[x]);
    }
    fclose(fileCParTwo);

	//Results ------------------------------------------------------------------------------------------
	printResultsAreTheSame();
	printResultsTable(resultSerial, resultParallel1, resultParallel2, averageSerial, averageParallel1, averageParallel2);
	printBestMethod(averageSerial, averageParallel1, averageParallel2);

   
    

	return 0;
}