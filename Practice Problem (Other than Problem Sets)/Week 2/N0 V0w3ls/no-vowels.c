// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string replace(string s);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage ./novowels word\n");
        return 1;
    }
    else
    {
        printf("%s\n", replace(argv[1]));
    }
}

string replace(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        // Interchanging letter using if else conditions
        if (tolower(s[i]) == 'a')
        {
            s[i] = '6';
        }
        else if (tolower(s[i]) == 'e')
        {
            s[i] = '3';
        }
        else if (tolower(s[i]) == 'i')
        {
            s[i] = '1';
        }
        else if (tolower(s[i]) == 'o')
        {
            s[i] = '0';
        }

        // Interchanging letter using switch statement
        switch(tolower(s[i]))
        {
            case 'a':         // Check whether tolower(s[i]) == 'a'
                s[i] = '6';

            case 'e':         // Check whether tolower(s[i]) == 'e'
                s[i] = '3';

            case 'i':         // Check whether tolower(s[i]) == 'i'
                s[i] = '1';

            case 'o':         // Check whether tolower(s[i]) == 'o'
                s[i] = '0';
        }
    }
    return s;
}


