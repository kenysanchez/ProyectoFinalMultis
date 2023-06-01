#include "Serial.h"

void runSerial()
{
	//for (int i = 0; i < 5; i++) {
	//
	//
	//
	////have the same number of rows as the 1st matrix, and the same number of columns as the 2nd matrix.
	////Matrix C rows = matARows, columns = matBColumns;
	//}
}

float multiplyMatrixes(float matA[], float matB[])
{
	return 0.0f;
}

void createMatrixC(float matC[])
{
	FILE* fileC;
	int matCSize = 0;

	errno_t errC = fopen_s(&fileC, "C:/Users/kenya/Desktop/ProyectoFinal/matrixC10.txt", "w");
	
	//TODO: Calcular matCsize 
	
	if (errC == 0) {
		for (int i = 0; i < matCSize; i++) {
			fprintf(fileC, "%f\n", matC[i]);
		}
	}
	else
	{
		printf("No se pudo abrir el archivo C\n");
	}

	if (fileC)
	{
		errC = fclose(fileC);
	}

}


