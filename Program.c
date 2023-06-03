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
    float* matrixA, matrixB;
    int countA = 0;
    int countB = 0;
    int memory = 0;
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
    float* arr = (float*)malloc(countA * sizeof(float));
    if (arr == NULL) {
        printf("Error: No hay suficiente espacio de memoria\n");
        return 0;
    }
    float* arrTemp = (float*)malloc(countA * sizeof(float));

    //Save values into array
    for (int i = 0; i < countA; i++) {
        fscanf(fileA, "%f", &arr[i]);
    }
    matA.fileRead = true;
    
    //Get file size B
    for (cB = getc(fileB); cB != EOF; cB = getc(fileB)){
        if (cB == '\n'){
            countB = countB + 1;
        }
    }
    printf("La matriz B tiene %d elementos \n", countB);
    fseek(fileB, 0, SEEK_SET);

    //Memory space validation
    float* arrB = (float*)malloc(countB * sizeof(float));
       
    if (arrB == NULL) {
        printf("Error: No hay suficiente espacio de memoria\n");
        return 0;
    }

    //Save values into array
    for (int i = 0; i < countB; i++) {
        fscanf(fileB, "%f\n", &arrB[i]);
    }
        matB.fileRead = true;


    //PRINT
    for (int i = 0; i < 10; i++) {
        fprintf("%f\n", &arr[i]);
    }

    transposeArray (arr, arrTemp, matA.columns, matA.rows);

    for (int i = 0; i < 10; i++) {
        fprintf("%f\n", &arrTemp[i]);
    }
       


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
        printf("Error: No se puede construir las matrices con esos valores. Intente de nuevo\n");
        return 0;
    }

    //TODO: Cargar los valores hacia matrices 
 
	//Serial--------------------------------------------------------------------------------------------



	//Parallel 1 ---------------------------------------------------------------------------------------
	
    //Parallel 2 ---------------------------------------------------------------------------------------

	//Results ------------------------------------------------------------------------------------------
	// printResultsAreTheSame();
	// printResultsTable();
	// printBestMethod();
	// generateMatrixC();

	return 0;
}