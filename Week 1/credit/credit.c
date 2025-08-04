#include <cs50.h>
#include <stdio.h>

typedef struct
{
    bool validNumber;
    int totalDigits;
} Result;

Result validateCreditCard(long wholeNo, int totalDigits);
int totalNoOfDigitsInNumber(long wholeNo);
long powerOfTen(int power);

int main(void)
{
    bool flag = false;
    long noToCheck;
    do
    {
        noToCheck = get_long("Number: ");
    }
    while (noToCheck <= 0);

    int total = totalNoOfDigitsInNumber(noToCheck);

    Result results = validateCreditCard(noToCheck, total);

    long temp = noToCheck;
    while (temp >= 100)
    {
        temp /= 10;
    }
    long LeftMostTwoDigits = temp;
    long LeftMostDigit = temp / 10;

    if (results.validNumber == true)
    {
        if (LeftMostDigit == 4 && (total == 13 || total == 16))
        {
            printf("VISA\n");
            flag = true;
        }
        else if ((LeftMostTwoDigits == 34 || LeftMostTwoDigits == 37) && total == 15)
        {
            printf("AMEX\n");
            flag = true;
        }
        else if ((LeftMostTwoDigits >= 51 && LeftMostTwoDigits <= 55) && total == 16)
        {
            printf("MASTERCARD\n");
            flag = true;
        }
        else
        {
            flag = false;
        }
    }
    if (flag != true)
    {
        printf("INVALID\n");
    }
    return 0;
}

long powerOfTen(int power)
{
    long number = 1;
    for (int x = 0; x < power; x++)
    {
        number *= 10;
    }
    return number;
}

int totalNoOfDigitsInNumber(long wholeNo)
{
    int dig = 0;
    while (wholeNo > 0)
    {
        wholeNo /= 10;
        dig++;
    }
    return dig;
}

Result validateCreditCard(long wholeNo, int totalDigits)
{
    Result result;
    int digit = 0;
    int finalSum = 0;
    int selectedDigit;
    int doubled;
    while (wholeNo > 0)
    {
        selectedDigit = wholeNo % 10;

        if (digit % 2 == 1) // The digit checks the index from right and total
                            // digit gives even number or odd number
        {
            doubled = selectedDigit * 2;
            if (selectedDigit >= 5)
            {
                finalSum += doubled / 10 + doubled % 10; // This adds the digits of the product.
            }
            else
            {
                finalSum += doubled;
            }
        }
        else
        {
            finalSum += selectedDigit;
        }

        wholeNo /= 10;
        digit++;
    }

    if (finalSum % 10 == 0)
    {
        result.validNumber = true;
        result.totalDigits = totalDigits;
    }
    else
    {
        result.validNumber = false;
        result.totalDigits = totalDigits;
    }

    return result;
}
