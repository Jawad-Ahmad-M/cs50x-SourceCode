#ifndef RLE_H
#define RLE_H
#include <stdio.h>

void rleCompress(const char* input , FILE* output);
void rleDecompress(FILE* input , FILE* output);
float comparisonRatio(FILE* original , FILE* compressed);
long getFileSize(char* fileName);

#endif
