#!/bin/sh

gcc -Wall -c -std=c99 IO/Matrix.c
gcc -Wall -c -std=c99 IO/Results.c
gcc -Wall -c -std=c99 IO/Validation.c
gcc -fopenmp -std=c99 -Wall -mavx512f -mavx512vl -c Methods/Parallel1.c
gcc -Wall -c -std=c99 Methods/Parallel2.c
gcc -Wall -c -std=c99 Methods/Serial.c
gcc -Wall -c -std=c99 Program.c
gcc -fopenmp -std=c99 -Wall -mavx512f -mavx512vl -O -o program Matrix.o Parallel1.o Parallel2.o Serial.o Results.o Validation.o Program.o


./program
