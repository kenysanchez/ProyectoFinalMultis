#ifndef RESULTS_DOT_H
#define RESULTS_DOT_H


#include <stdio.h>
#include <stdbool.h>

struct Results
{
	int bestMethod;
};

void printResultsAreTheSame();
bool calculateIfBothResultsAreTheSame();
void printResultsTable(double *resultSerial, double * resultParallel1, double * resultParallel2, double averageSerial, double averageParallel1, double averageParallel2);
int calculateBestMethod(double averageSerial, double averageParallel1, double averageParallel2 );
void printBestMethod(double averageSerial, double averageParallel1, double averageParallel2);
double getAverage(double *result);

#endif