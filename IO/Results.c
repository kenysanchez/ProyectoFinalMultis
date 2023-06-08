#include "../HeaderFiles/Results.h"

void printResultsAreTheSame()
{
	const char *file1 = "matrixCSer.txt";
    const char *file2 = "matrixCParOne.txt";
	const char *file3 = "matrixCParTwo.txt";

	printf("\n_____________RESULTADOS_____________\n");
	if (calculateIfBothResultsAreTheSame(file1, file2)) {
		printf("El resultado del parallel 1 es igual al serial\n");
	}
	else {
		printf("El resultado del parallel 1 NO es igual al serial\n");
	}

	if (calculateIfBothResultsAreTheSame(file1, file3)) {
		printf("El resultado del parallel 2 es igual al serial\n");
	}
	else {
		printf("El resultado del parallel 2 es igual al serial\n");
	}
}

bool calculateIfBothResultsAreTheSame(const char *file1, const char *file2)
{
	FILE *fileSerial  = fopen(file1, "r");
	FILE *filePar  = fopen(file2, "r");
	int char1, char2;

	if (fileSerial == NULL) {
        printf("No se pudo abrir el archivo %s\n", fileSerial);
        return -1;
    }
	if (filePar == NULL) {
        printf("No se pudo abrir el archivo %s\n", filePar);
        return -1;
    }

	while ((char1 = fgetc(fileSerial)) != EOF && (char2 = fgetc(filePar)) != EOF) {
        if (char1 != char2) {
            fclose(fileSerial);
            fclose(filePar);
            return 0;
        }
    }

	if (char1 == EOF && char2 == EOF) {
        fclose(fileSerial);
        fclose(filePar);
        return 1; 
    }

	fclose(fileSerial);
	fclose(filePar);
}

void printResultsTable(double *resultSerial, double *resultParallel1, double *resultParallel2, double averageSerial, double averageParallel1, double averageParallel2)
{
	char *row1[] = { "C  ", "  S  ", "    P1  ", "    P2  " };
	char *column1[] = { "1 ", "2 ", "3 ", "4 ", "5 ", "P ", "% "};

	printf("\n_______TABLA DE RESULTADOS_______\n");
	
	for (int i = 0; i < 4; i++) {
        printf("%s", row1[i]);
    }
	printf("\n");

	for (int i = 0; i < 5; i++) {
		printf("%s %.6f %.6f %.6f", column1[i], resultSerial[i], resultParallel1[i], resultParallel2[i]);	
		printf("\n");
	}
	printf("%s %.6f %.6f %.6f\n", column1[5], averageSerial, averageParallel1, averageParallel2);	
	printf("%s %.6f %.6f %.6f\n", column1[6], 0.0, averageParallel1/averageSerial, averageParallel2/averageSerial);	
}

int calculateBestMethod(double averageSerial, double averageParallel1, double averageParallel2)  
{
	double fastest = averageSerial;
	int method;

	if(averageParallel1 < fastest){
		fastest = averageParallel1;
		method = 1;
	}
	else if(averageParallel2 < fastest){
		fastest = averageParallel2;
		method = 2;
	}
	else{
		fastest = averageSerial;
		method = 3;
	}
	
	return method;
}

void printBestMethod(double averageSerial, double averageParallel1, double averageParallel2)
{
	char* methods[] = { "Serial", "Parallel 1 ", "Parallel 2"};

	int bestMethod = calculateBestMethod(averageSerial, averageParallel1, averageParallel2);

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

double getAverage(double *array) 
{
	double sum;

	for (int i = 0; i < 5; i++) {
		sum = array[i];
	}
	
	if (sum == 0){
		return 0;
	}
	else {
		return sum / 5;
	}
}

