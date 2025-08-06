// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function
float half(float bill, float tax, int tip)
{
    // Calculates total taxes by getting that percentage
    float totalTax = bill * tax / 100.0;

    // Adds Taxes in Bill
    float billAfterTax = bill + totalTax;

    // Calculates tip based on percentage given
    float totalTip = billAfterTax * tip / 100.0;

    // Adds taxes in current bill e.g Bill including Taxes
    float totalBillAfterTip = billAfterTax + totalTip;

    // returning the half of our Calculated Bill
    return totalBillAfterTip / 2.0;

    return (bill * (1 + (tax / 100.0)) * (1 + (tip / 100.0))) / 2.0; // all done in one line.
}
