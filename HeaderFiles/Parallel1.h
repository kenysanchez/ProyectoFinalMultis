#ifndef PARALLEL2_DOT_H
#define PARALLEL1_DOT_H
#include <stdio.h>
#include <omp.h>
#include <sys/time.h>


struct Parallel1
{
	float run1, run2, run3, run4, run5, average, percentageVsSerial;
};

nt rowsA, int colsA, int rowsB, int colsB, double *arrA, double *arrB, FILE *pFile, double *resulvoid runParallel1(itParallel1);
void parMultiplyMatrixes(int rowsA, int colsA, int rowsB, int colsB, double *arrA, double *arrB, FILE *pFile);

#endif