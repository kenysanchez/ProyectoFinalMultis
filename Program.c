#include <stdio.h>
#include "MatrixValidation.h"
#include "Parallel1.h"
#include "Parallel2.h"
#include "Serial.h"
#include "Results.h"


int main() {
	struct MatrixValidation matrixValidation;
	struct Results results;
	struct Serial serial;
	struct Parallel1 parallel1;
	struct Parallel2 parallel2;


	//Initialization
	int matAColumna, matAFila, matBColumna, matBFila;

	printf("Matriz A\n");
	printf("Ingresa la cantidad de columnas de la matriz: \n");
	scanf_s("%d", &matAColumna);
	printf("Ingresa la cantidad de filas de la matriz: \n");
	scanf_s("%d", &matAFila);

	printf("\nMatriz B\n");
	printf("Ingresa la cantidad de columnas de la matriz: \n");
	scanf_s("%d", &matBColumna);
	printf("Ingresa la cantidad de filas de la matriz: \n");
	scanf_s("%d", &matBFila);

	readFile();

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