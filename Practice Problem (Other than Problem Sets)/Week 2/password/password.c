// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h> 

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and "
               "symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool uppercase = false, lowercase = false, number = false, symbol = false;

    for (int i = 0; i < strlen(password); i++)
    {
        if (password[i] >= 'A' && password[i] <= 'Z') // Check whether the character is uppercase
        {
            uppercase = true;
        }
        else if (password[i] >= 'a' &&
                 password[i] <= 'z') // Check whether the character is lowercase
        {
            lowercase = true;
        }
        else if (isdigit(password[i])) // Checks whether the character is digit or not
        {
            number = true;
        }
        else
        {
            if (password[i] != ' ') // It was additional but, I say that space
            {                       // must not be included in password as symbol
                symbol = true;
            }
        }
    }

    if (uppercase == lowercase && number == symbol &&
        symbol == true) // Checks All condition to be true
    {
        return true;
    }

    return false; // If all conditions not true then false is returned.
}
