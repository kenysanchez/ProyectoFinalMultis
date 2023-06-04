#include <stdio.h>
#include <stdlib.h>
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
    double* matrixA, matrixB;
    int countA = 0;
    int countB = 0;
    char cA, cB;

    FILE *fileA  = fopen("./Test/matrixA10.txt", "r");
    FILE *fileB  = fopen("./Test/matrixB10.txt", "r");
    
    //Get file size A
    for (cA = getc(fileA); cA != EOF; cA = getc(fileA))
            if (cA == '\n')
                countA = countA + 1;
    printf("La matriz A tiene %d elementos\n", countA);
    fseek(fileA, 0, SEEK_SET);

    //Memory space validation
    double* arrA = (double*)malloc(countA * sizeof(double));
    if (arrA == NULL) {
        printf("Error: No hay suficiente espacio de memoria\n");
        return 0;
    }
    double* arrTemp = (double*)malloc(countA * sizeof(double));
    if (arrTemp == NULL) {
        printf("Error: No hay suficiente espacio de memoria\n");
        return 0;
    }


    //TEMP
    //Save values into array
    // for (int i = 0; i < countA; i++) {
    //     scanf(fileA, "%f", &arrA[i]);
    //      printf("%.12f\n", arrA[i]);
    // }

    float num;
    int n = 0;
    while( fscanf(fileA, "%f", &num) != EOF ) {
        arrA[n++] = num;
    }
    matA.fileRead = true;
    
    // //Get file size B
    // for (cB = getc(fileB); cB != EOF; cB = getc(fileB)){
    //     if (cB == '\n'){
    //         countB = countB + 1;
    //     }
    // }
    // printf("La matriz B tiene %d elementos \n", countB);
    // fseek(fileB, 0, SEEK_SET);

    // //Memory space validation
    // double* arrB = (double*)malloc(countB * sizeof(double));
       
    // if (arrB == NULL) {
    //     printf("Error: No hay suficiente espacio de memoria\n");
    //     return 0;
    // }

    // //Save values into array
    // for (int i = 0; i < countB; i++) {
    //     fscanf(fileB, "%f\n", arrB[i]);
    // }
    //     matB.fileRead = true;


    //PRINT
    printf("BEFORE MAT A\n");
    for (int i = 0; i < 10; i++) {
        printf("%.12f\n", arrA[i]);
    }

    // transposeArray (arr, arrTemp, matA.columns, matA.rows);

    // printf("AFTER MAT A\n");
    // for (int i = 0; i < 10; i++) {
    //     printf("%.12f\n", &arrTemp[i]);
    // }
       


	// //Validation-----------------------------------------------------------------------------------------
    // if (canBuildMatrix(countA, matA.columns, matA.rows) && canBuildMatrix(countB, matB.columns, matB.rows)){
    //     printf("Si se pueden crear las matrices con esos ...\n");
    //     if (matrixMultiplication(matA.columns, matA.rows, matB.columns, matB.rows)) {
    //         printf("Si se pueden multiplicar las matrices...\n");
    //     }
    //     else {
    //         printf("Error: No se pueden multiplicar las matrices con esos valores. Intente de nuevo\n");
    //         return 0;
    //     }
    // }
    // else {
    //     printf("Error: No se puede construir las matrices con esos valores. Intente de nuevo\n");
    //     return 0;
    // }

    //TODO: Cargar los valores hacia matrices 
 






	//Serial--------------------------------------------------------------------------------------------



	//Parallel 1 ---------------------------------------------------------------------------------------
	
    //Parallel 2 ---------------------------------------------------------------------------------------

	//Results ------------------------------------------------------------------------------------------
	// printResultsAreTheSame();
	// printResultsTable();
	// printBestMethod();
	// generateMatrixC();

    fclose(fileA);
    fclose(fileB);

	return 0;
}