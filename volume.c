// Modifies the volume of an audio file

#include <stdio.h>  /* FILE * (file type declaration), fopen (open file),
                       fclose (close file), fread (read from file),
                       fwrite (write to file)                             */
#include <stdint.h> /* uint8_t (8-bit unsigned integer),
                       int16_t (16-bit signed integer)   */
#include <stdlib.h> // atof (converts string to floating point number)

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

    // Determine scaling factor
    float factor = atof(argv[3]);

    /* Copy header from input file to output file
       (NOTE: WAV header size is 44 bytes)        */
    const int HEADER_SIZE = 44;
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // Read samples from input file and write updated data to output file
    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
