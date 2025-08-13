// #include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    // Opens the card file

    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("The file is not opened. Try with a new file.\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    FILE *output = NULL;
    char filename[8];
    int fileCount = 0;

    while (fread(buffer, BLOCK_SIZE, 1, card) == 1)
    {
        // Check all conditions i.e First 4 bytes
        int isStart = (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
                       (buffer[3] & 0xf0) == 0xe0)
                          ? 1
                          : 0;

        if (isStart == 1)
        {
            if (output != NULL) // If pervious file opened has some data
            {
                fclose(output); // Closes that previous file
            }

            sprintf(filename, "%03i.jpg", fileCount); // Make the file according to the given format
                                                      // like 000.jpg, 001.jpg and so on.
            output = fopen(filename, "w"); // Creates the file with that name in write mode
            fileCount++;
        }

        if (output != NULL) // Check if previous file contains any data.
        {
            fwrite(buffer, BLOCK_SIZE, 1, output); // If yes then add buffer to that same file.
        }
    }

    if (output != NULL) // After the loop if the file is open then close it.
    {
        fclose(output);
    }

    fclose(card); // Finally closing the file which contains the data before quiting the program.
    return 0;
}
