#include "../HeaderFiles/Results.h"

void printResultsAreTheSame()
{
	printf("\n_____________RESULTADOS_____________\n");
	if (calculateIfBothResultsAreTheSame) {
		printf("Los resultados de los codigos paralelos son identicos al serial\n");
	}
	else {
		printf("Los resultados de los codigos paralelos NO son identicos al serial\n");
	}
}

bool calculateIfBothResultsAreTheSame()
{
	//TODO: Calcular si todos los resultados son iguales
	return false;
}

void printResultsTable()
{
	//TODO: Mejorar el aesthetic de la tabla 
	int rows = 7;
	int	columns = 3;

	char *row1[] = { "C ", "S ", "P1 ", "P2" };
	char *column1[] = { "1 ", "2 ", "3 ", "4 ", "5 ", "P ", "% "};

	printf("\n_______TABLA DE RESULTADOS_______\n");

	for (int k = 0; k < 4; k++) {
		printf("%s", row1[k]);
	}
	printf("\n");

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (j == 0) {
				printf("%s", column1[i]);
			}
			printf("X ");
		}
		printf("\n");
	}
}

int calculateBestMethod()  
{
	//TODO: Calcular mejor metodo
	return 0;
}

void printBestMethod()
{
	char* methods[] = { "Serial", "Parallel 1 ", "Parallel 2"};

	int bestMethod = calculateBestMethod();

	printf("\n_______METODO MAS RAPIDO_______");
	if (bestMethod == 0) {
		printf("\nEl metodo mas rapido es el %s\n", methods[0]);
	}
	else if (bestMethod == 1) {
		printf("\nEl metodo mas rapido es el %s\n", methods[1]);
	}
	else {
		printf("\nEl metodo mas rapido es el %s\n", methods[2]);
	}
}

void generateMatrixC()
{
	//Generar archivo matriz C de resultado
	printf("\n___GENERACION DE ARCHIVO MATRIZ C___");
	printf("\nSe genero el archivo matrizC.txt\n\n");
}

float getAverage(int time[5]) 
{
	//TODO: Probar funcion
	int sum;

	for (int i = 0; i < 5; i++) {
		sum = time[i];
	}
	if (sum == 0){
		return 0;
	}
	else {
		return sum / 5;
	}
}

void percentageVsSerial()
{
	//TODO:  Calcular el porcentaje
}
