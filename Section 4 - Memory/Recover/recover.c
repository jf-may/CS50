#include <stdio.h>
#include <stdlib.h>
#include "recover.h"
 
int main(int argc, char *argv[])
{
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

    // Open null output file and buffer
    FILE *output = NULL;
    const int BUFFER_SIZE = 512;
    BYTE buffer[BUFFER_SIZE];
    int count = 0;

    // Read input file in blocks of 512 bytes
    while (fread(buffer, 1, BUFFER_SIZE, input))
    {
        // Check for JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            if (output != NULL)
            {
                fclose(output);
            }

            // Open new output file
            char filename[8];
            sprintf(filename, "%03i.jpg", count);
            output = fopen(filename, "w");
            if (output == NULL)
            {
                printf("Could not create output file.\n");
                fclose(input);
                return 1;
            }

            count++;
        }
        // Check for open file and write buffer to it
        if (output != NULL)
        {
            fwrite(buffer, 1, BUFFER_SIZE, output);
        }
    }

    // Close files
    fclose(input);
    if (output != NULL)
    {
        fclose(output);
    }

    return 0;
}
