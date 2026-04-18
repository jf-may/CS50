// Modifies the volume of an audio file

#include <stdio.h> // FILE *, fopen, fclose
#include <stdlib.h> // atof

int main(int argc, char *argv[]) 
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open input file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    // Open output file
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open output file.\n");
        return 1;
    }

    // Determine scaling factor (NOTE: atof converts string to floating point number)
    float factor = atof(argv[3]);

    // Copy header from input file to output file (NOTE: WAV header size is 44 bytes)
    const int HEADER_SIZE = 44;

    // Read samples from input file and write updated data to output file

    // Close files
    fclose(input);
    fclose(output);
}