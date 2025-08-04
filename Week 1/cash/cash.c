#include <cs50.h>
#include <stdio.h>

void totalQuaters(int *change, int *coins, int value);

int main(void)
{
    int change;
    int coins = 0;
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 0);

    totalQuaters(&change, &coins, 25);
    totalQuaters(&change, &coins, 10);
    totalQuaters(&change, &coins, 5);
    totalQuaters(&change, &coins, 1);

    printf("%d\n", coins);
}

void totalQuaters(int *change, int *coins, int value)
{
    while (*change >= value)
    {
        *change = *change - value;
        (*coins)++;
    }
}
