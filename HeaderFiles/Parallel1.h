#ifndef PARALLEL2_DOT_H
#define PARALLEL1_DOT_H
#include <stdio.h>
#include <omp.h>
#include <sys/time.h>


struct Parallel1
{
	float run1, run2, run3, run4, run5, average, percentageVsSerial;
};

void runParallel1(int rowsA, int colsA, int rowsB, int colsB, double *arrA, double *arrB, double *arrC);
void parMultiplyMatrixes(int rowsA, int colsA, int rowsB, int colsB, double *arrA, double *arrB, double *arrC);


#endif