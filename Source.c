#include <stdio.h>

int main() {

	//Inicializacion
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
	return 0;
}