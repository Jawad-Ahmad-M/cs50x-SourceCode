#include "rle.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void rleCompress(const char* input, FILE* output)
{
    int length = strlen(input);

    for (int i = 0; i < length; i++)
    {
        char character = input[i];
        int count = 1;

        while ( i + 1 < length && input[i] == input[i+1])
        {
            count++;
            i++;
        }

        fprintf(output, "%c%d", character, count);

    }

}


void rleDecompress(FILE* input, FILE* output)
{
    char character;
    int count;

    while (fscanf(input, "%c%d", &character, &count) != EOF)
    {
        for (int i = 0; i < count; i++)
        {
            fputc(character, output);
        }
    }

}

float comparisonRatio(FILE* originalFile, FILE* compressedFile)
{
    fseek(originalFile, 0, SEEK_END);
    long originalLength = ftell(originalFile);
    rewind(originalFile);

    fseek(compressedFile, 0, SEEK_END);
    long compressedLength = ftell(compressedFile);
    rewind(compressedFile);

    return (float) originalLength / compressedLength;
}

long getFileSize(char* fileName)
{
    struct stat file_stat;

    if(stat(fileName, &file_stat) == -1)
    {
        printf("The stat function didn't procceded succesfully.");
        return -1;
    }

    return file_stat.st_size;
}
