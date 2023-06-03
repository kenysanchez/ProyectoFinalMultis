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
void printResultsTable();
int calculateBestMethod( );
void printBestMethod();
void generateMatrixC();
float getAverage(int time[5]);
void percentageVsSerial();

#endif