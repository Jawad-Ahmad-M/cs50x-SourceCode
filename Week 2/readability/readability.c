#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int GradeMeasuring(int length, string text);

int main(void)
{
    string inputText = get_string("Text: ");

    int gradeIndex = GradeMeasuring(strlen(inputText), inputText);

    if (gradeIndex >= 1 && gradeIndex <= 16)
    {
        printf("Grade %d\n", gradeIndex);
    }
    else if (gradeIndex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (gradeIndex > 16)
    {
        printf("Grade 16+\n");
    }
}

int GradeMeasuring(int length, string text)
{
    int sentences = 0;
    int words = 1;
    int letters = 0;

    for (int i = 0; i < length; i++)
    {
        if (text[i] == '?' || text[i] == '.' || text[i] == '!')
        {
            sentences++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }
        else if (isalpha(text[i]))
        {
            letters++;
        }
    }

    float L = (letters / (float) words) * 100;
    float S = (sentences / (float) words) * 100;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}
