#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    for (int i = 2; i < number; i++) // Loop moves from 2-Number provided excluding the number.
    {
        if (number % i == 0) // Check wether the number is exactly divisble
        {
            return false; // if any number divides then return false meaning this is not a prime no.
        }
    }
    return true; // if all for loop executes meaning no number exactly divides given number
                 // then return true meaning the no is prime.
}
