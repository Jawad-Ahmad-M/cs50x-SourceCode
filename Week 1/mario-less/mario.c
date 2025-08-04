#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int noOfLines;

    // The code to get the input of height

    do
    {
        noOfLines = get_int("Height :");
    }
    while (noOfLines < 1); // Invalidations

    // Code for making the pyramid

    for (int i = 0; i < noOfLines; i++)
    {

        for (int j = 0; j < noOfLines - i - 1; j++)
        {
            printf(" ");
        }

        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}
