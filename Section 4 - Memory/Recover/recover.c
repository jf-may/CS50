#include <stdio.h>
#include <stdlib.h>
#include "recover.h"
 
int main(int argc, char *argv[])
{
    const int BUFFER_SIZE = 512;
    int count = 0;
    BYTE buffer[BUFFER_SIZE];

    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open input file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    // Mientras haya bloques para leer, entrá al loop
    while (fread(buffer, 1, BUFFER_SIZE, input) == BUFFER_SIZE)
    {
        // Si la signature es la correcta, entrá al loop
        if (buffer[0] != 0xff || buffer[1] != 0xd8 || buffer[2] != 0xff ||
            buffer[3] < 0xe0 || buffer[3] > 0xef)
        {
            // Si la signature es la correcta, se abre un nuevo archivo
            count++;
            FILE *output = fopen(("%03i.jpg", count), "w");

            // TODO: Ahora hay que leer bloques y agregarlos al archivo hasta que haya otra signature, en cuyo caso se cierra el file anterior y se abre otro
            fwrite(buffer, 1, BUFFER_SIZE, output);
        }
    }

    // Close files
    fclose(input);
}