#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isOnlyDigit(string s);

int main(int argc, string argv[])
{
    if (argc == 2 && isOnlyDigit(argv[1]))
    {
        int key = atoi(argv[1]);
        if (key == 0)
        {
            return 1;
        }
        int POSITION_CHANGE = key % 26;

        string input = get_string("plaintext:  ");

        for (int i = 0, n = strlen(input); i < n; i++)
        {
            char resultChar = input[i] + (POSITION_CHANGE);
            if (islower(input[i]))
            {
                input[i] = 'a' + (input[i] - 'a' + POSITION_CHANGE) % 26;
            }
            else if (isupper(input[i]))
            {
                input[i] = 'A' + (input[i] - 'A' + POSITION_CHANGE) % 26;
            }
            else
            {
                input[i] = input[i];
            }
        }

        printf("ciphertext: %s\n", input);
    }
    else
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
}

bool isOnlyDigit(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}
