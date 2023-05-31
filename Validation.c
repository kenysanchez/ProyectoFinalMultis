#include "Validation.h"

void readFile()
{
    FILE* stream;
    errno_t err;

    err = fopen_s(&stream, "./matrixA2500.txt", "r");
    
    if (err == 0)
    {
            printf("The file 'matrixA2500.txt' was opened\n");
    }
    else
        {
            printf("The file 'matrixA2500.txt' was not opened\n");
        }

    // Close stream if it isn't NULL
        if (stream)
        {
            err = fclose(stream);
            if (err == 0)
            {
                printf("The file 'crt_fopen_s.c' was closed\n");
            }
            else
            {
                printf("The file 'crt_fopen_s.c' was not closed\n");
            }
        }
        return 0;
}

bool canBuildMatrix(int matrixSize)
{
    return false;
}

bool matrixMultiplication(bool matA, bool matB)
{
    return false;
}

bool enoughMemorySpace(int memorySpace)
{
    return false;
}
