#!/bin/sh

gcc -Wall -c IO/Matrix.c
gcc -Wall -c IO/Results.c
gcc -Wall -c IO/Validation.c
gcc -fopenmp -mavx2 -Wall -c Methods/Parallel1.c
nvcc -c Methods/Parallel2.cu -o Parallel2.o
gcc -Wall -c Methods/Serial.c
gcc -Wall -c Program.c

gcc -fopenmp -mavx2  -o program *.o -lcudart -lcuda


./program
