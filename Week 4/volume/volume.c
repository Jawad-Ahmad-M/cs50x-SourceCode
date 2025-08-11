// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t BYTE;
typedef int16_t DoubleBYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    BYTE byte;
    DoubleBYTE dbyte;

    BYTE header[HEADER_SIZE];
    fread(&header, sizeof(header), 1, input);   // Reads Header
    fwrite(&header, sizeof(header), 1, output); // Writes Header

    while (fread(&dbyte, sizeof(DoubleBYTE), 1, input) == 1) // Reads all Samples till end one
    {
        dbyte = dbyte * factor; // Increases or Decreases the sample based on volume
        fwrite(&dbyte, sizeof(DoubleBYTE), 1, output); // Writes that sample volume with change
    }

    // Close files
    fclose(input);
    fclose(output);
}
