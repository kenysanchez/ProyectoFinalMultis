#!/bin/sh

gcc -Wall -c IO/Matrix.c
gcc -Wall -c IO/Results.c
gcc -Wall -c IO/Validation.c
gcc -Wall -c Methods/Parallel1.c
gcc -Wall -c Methods/Parallel2.c
gcc -Wall -c Methods/Serial.c
gcc -Wall -c Program.c

gcc -o program Matrix.o Parallel1.o Parallel2.o Serial.o Results.o Validation.o Program.o


./program