#ifndef SERIAL_DOT_H
#define SERIAL_DOT_H

#include <stdio.h>

struct Serial
{
	float run1, run2, run3, run4, run5, average;
};

void runSerial();
void multiplyMatrixes(); //TODO: Agregar params

#endif