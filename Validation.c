#include "Validation.h"


void readFile(int columns, int rows)
{
    //TODO: Leer docs http://labsopa.dis.ulpgc.es/fso/cpp/intro_c/introc75.htm

    FILE* stream;
    float* arr;
    int count = 1;
    char c;
    float fp;

    //TODO: Cambiar path a dinamico
    errno_t err = fopen_s(&stream, "C:/Users/kenya/Desktop/ProyectoFinal/matrixA10.txt", "r");
    
    if (err == 0) {
        printf("The file was opened\n");
        
        //Revisar cuantos valores son 
        for (c = getc(stream); c != EOF; c = getc(stream))
            if (c == '\n') 
                count = count + 1;
        printf("File size %d \n", count);
        
        
        //Guardar los datos en un arreglo
        arr = (float*)malloc (count*sizeof(float));
        
        //Asignar los valores al arreglo
        for (int i = 0; i < count; i++) {
            fscanf_s(stream, "%f", &fp);
            arr[i] = fp;
        }

        for (int i = 0; i < 10; i++) {
            printf("%.10f\n", arr[i]);
        }

    } 
    else {
        printf("The file was not opened\n");
    }
   
    // Close stream if it isn't NULL
        if (stream)
        {
            err = fclose(stream);
            (err == 0) ? printf("The file was  closed\n") : printf("The file was not closed\n");
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
