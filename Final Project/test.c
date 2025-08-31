#include "rle.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void printUsage();
void helperFunctionSingleFile(char* mode, char* inputFile, char* outputfile);
void helperFunctionMultipleInputs(char* mode, char** files, int argc);
char** subsetList(char* names[], int start,int end);


int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        printUsage();
        return 1;
    }

    if (argc == 4)
    {
        char* mode = argv[1];
        char* inputFile = argv[2];
        char* outputFile = argv[3];

        helperFunctionSingleFile(mode, inputFile, outputFile);
    }
    else if (argc > 4)
    {
        char* mode = argv[1];

        int start = 3;
        int end = argc;

        int size = end - start + 1;

        char** files = subsetList(argv, start, end);

        helperFunctionMultipleInputs(mode, files, argc);


    }

}

char** subsetList(char* names[], int start,int end)
{
    int size = end - start + 1;

    char** subset = (char**)malloc(size * sizeof(char*));
    if (subset == NULL)
    {
        printf("Sizing failed for sublisting!!!");
        return NULL;
    }

    memcpy(subset, &names[start], size * sizeof(char*));

    return subset;
}

void printUsage()
{
    printf("Usage 1: ./text <-c(for compression) or -d(decompression)> inputfile.txt outputfile.txt\n");
    printf("Usage 2: ./text <-c(for compression) or -d(decompression)> -m(for multiple files) 1.txt 2.txt ....\n");
}

void helperFunctionMultipleInputs(char* mode, char** files , int argc)
{
    for (int i = 0; i < argc; i++)
        {
            char* inputFilename = files[i];
            char outputFilename[strlen(inputFilename) + 10];
            sprintf(outputFilename, "output_%s", files[i]);
            helperFunctionSingleFile(mode, inputFilename, outputFilename);
        }
}

void helperFunctionSingleFile(char* mode, char* inputFile, char* outputFile)
{
    FILE* input = fopen(inputFile, "r");

    if(!input)
    {
        printf("ERROR : The input file is not present!!!\n");
    }

    FILE* output = fopen(outputFile, "w");

    char* value = "decreased";

    if (strcmp(mode, "-c") == 0)
    {
        char buffer[1024];
        fread(buffer, 1, sizeof(buffer), input);
        rleCompress(buffer, output);
    }
    else if (strcmp(mode, "-d") == 0)
    {
        rleDecompress(input, output);
        value = "increased";
    }
    else
    {
        printUsage();
        fclose(input);
        fclose(output);
    }
    # BOTH OF THESE FUNCTION RETURN SAME VALUE, YOU CAN CHECK THE CODE IN rle.c file.
    # It tells us whether the size of file is increased or decreased, it gives value in percentages.
    printf("The value by Which size %s is %.2f%%\n", value, round(100 / comparisonRatio(input, output)));
    printf("The value by Which size %s is %.2f%%\n", value, 100 / ((float)getFileSize(inputFile) / getFileSize(outputFile)));

    fclose(input); #
    fclose(output);
}
