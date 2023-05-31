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


	//Initialization
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

	readFile();

	//Validation


	//Serial
	//Parallel 1
	//Parallel 2 

	//Results 
	printResultsAreTheSame();
	printResultsTable();
	printBestMethod();
	generateMatrixC();

	return 0;
}