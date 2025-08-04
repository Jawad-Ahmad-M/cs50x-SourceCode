#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validateFunction(string s, char newPair[26]);

int main(int argc, string argv[])
{
    char keyPair[26];
    if (argc != 2 || !validateFunction(argv[1], keyPair))
    {
        printf("Error in Key\n");
        printf("%d", argc);
        return 1;
    }
    else
    {
        string input = get_string("plaintext:  ");

        int length = strlen(input);

        char output[length];

        for (int i = 0; i < length; i++)
        {
            if (isupper(input[i]))
            {
                output[i] = toupper(keyPair[input[i] - 'A']);
            }
            else if (islower(input[i]))
            {
                output[i] = tolower(keyPair[input[i] - 'a']);
            }
            else
            {
                output[i] = input[i];
            }
        }
        output[length] = '\0';
        printf("ciphertext: %s\n", output);
    }

    return 0;
}

bool validateFunction(string s, char newPair[26])
{
    if (strlen(s) != 26)
    {
        return false;
    }
    else
    {
        for (int i = 0, n = strlen(s); i < n; i++)
        {
            if (!isalpha(s[i]))
            {
                return false;
            }
            if (i == 0)
            {
                newPair[0] = s[i];
            }
            for (int j = 0; j < i; j++)
            {
                if (tolower(s[i]) == tolower(newPair[j]))
                {
                    return false;
                }
            }
            newPair[i] = toupper(s[i]);
        }
    }

    return true;
}
