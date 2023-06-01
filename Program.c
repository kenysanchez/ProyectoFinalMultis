#include <stdio.h>
#include "Matrix.h"
#include "Validation.h"
#include "Parallel1.h"
#include "Parallel2.h"
#include "Serial.h"
#include "Results.h"


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
	scanf_s("%d", &matA.columns);
	printf("Ingresa la cantidad de filas de la matriz: \n");
	scanf_s("%d", &matA.rows);

	printf("\nMatriz B\n");
	printf("Ingresa la cantidad de columnas de la matriz: \n");
	scanf_s("%d", &matB.columns);
	printf("Ingresa la cantidad de filas de la matriz: \n");
	scanf_s("%d", &matB.rows);

	//Reading files-----------------------------------------------------------------------------
    FILE* fileA;
    FILE* fileB;
    float* matrixA, matrixB;
    int countA = 1;
    int countB = 1;
    int memory = 0;
    char cA, cB;

    errno_t errA = fopen_s(&fileA, "C:/Users/kenya/Desktop/ProyectoFinal/matrixA10.txt", "r");
	errno_t errB = fopen_s(&fileB, "C:/Users/kenya/Desktop/ProyectoFinal/matrixB10.txt", "r");

    if (errA == 0) {
        for (cA = getc(fileA); cA != EOF; cA = getc(fileA))
            if (cA == '\n')
                countA = countA + 1;
        printf("La matriz A tiene %d elementos\n", countA);
        fseek(fileA, 0, SEEK_SET);

        float* arr = (float*)malloc(countA * sizeof(float));


        for (int i = 0; i < countA; i++) {
            fscanf_s(fileA, "%f", &arr[i]);
        }

        matA.fileRead = true;
    }
    else {
        printf("No se pudo abrir el archivo A\n");
        return 0;
    }

    if (errB == 0) {

        for (cB = getc(fileB); cB != EOF; cB = getc(fileB))
            if (cB == '\n')
                countB = countB + 1;
        printf("La matriz B tiene %d elementos \n", countB);
        fseek(fileB, 0, SEEK_SET);

        float* arrB = (float*)malloc(countB * sizeof(float));

        for (int i = 0; i < countB; i++) {
            fscanf_s(fileB, "%f", &arrB[i]);
        }
        matB.fileRead = true;
    }
    else {
        printf("No se pudo abrir el archivo B\n");
        return 0;
    }

    if (fileA)
    {
        errA = fclose(fileA);
    }
    if (fileB)
    {
        errB = fclose(fileB);
    }

	//Validation-----------------------------------------------------------------------------------------
    if (canBuildMatrix(countA, matA.columns, matA.rows) && canBuildMatrix(countB, matB.columns, matB.rows)){
        printf("Validando si se pueden crear las matrices...\n");
        if (matrixMultiplication(matA.columns, matA.rows, matB.columns, matB.rows)) {
            printf("Validando si se pueden multiplicar las matrices...\n");
            //TODO: Checar validacion
            /*if (enoughMemorySpace(memory)) {
                printf("Validando si hay suficiente espacio de memoria...\n");
            }
            else {
                printf("Error: No hay suficiente espacio de memoria\n");
                return 0;
            }*/
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
	printResultsAreTheSame();
	printResultsTable();
	printBestMethod();
	generateMatrixC();

	return 0;
}