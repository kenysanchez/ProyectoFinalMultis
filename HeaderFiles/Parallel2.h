#ifndef PARALLEL2_DOT_H
#define PARALLEL2_DOT_H
#include <stdio.h>

struct Parallel2
{
	float run1, run2, run3, run4, run5, average, percentageVsSerial;
};

void runParallel2();

#endif