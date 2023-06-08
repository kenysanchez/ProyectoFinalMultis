#ifndef SERIAL_DOT_H
#define SERIAL_DOT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

struct Serial
{
	float run1, run2, run3, run4, run5, average;
};

void runSerial(int rowsA, int colsA, int rowsB, int colsB, double *arrA, double *arrB, FILE *pFile, double *resultSerial);
void multiplyMatrixes(int rowsA, int colsA, int rowsB, int colsB, double *arrA, double *arrB, FILE *pFile);

#endif