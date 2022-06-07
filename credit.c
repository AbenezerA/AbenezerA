#include <cs50.h>
#include <stdio.h>

//header for later method
int fancy(int num);

int main(void)
{
    //get input from user and calculate the number of digits
    long card = get_long("Enter Credit Card Number: ");
    int digits = 0;
    long n = card;
    while (n > 0)
    {
        digits++;
        n /= 10;
    }

    //calculating the regular and fancy sums while alternating between digits
    int digRem = 0;
    int sumRegular = 0;
    int sumFancy = 0;
    int firstDigit = 0, secondDigit = 0;
    while (digRem < digits)
    {
        //get the digit to be considered and move pointer to next digit
        int digCons = card % 10;
        card /= 10;
        //check if the digit fits the regular sum or fancy sum model and add it accordingly
        if (digRem % 2 == 0)
        {
            sumRegular += digCons;
        }
        else
        {
            sumFancy += fancy(digCons);
        }
        //get the first and second digits for precise validation and card type pin-pointing
        if (digRem == digits - 2)
        {
            secondDigit = digCons;
        }
        if (digRem == digits - 1)
        {
            firstDigit = digCons;
        }
        digRem++;
    }

    //calculates big final sum and validates
    bool isValid = false;
    if ((sumRegular + sumFancy) % 10 == 0)
    {
        isValid = true;
    }

    //final validation and printing out of card-type if valid
    if (isValid)
    {
        //if the card meeets the criteria for american express...
        if (digits == 15 && firstDigit == 3 && (secondDigit == 4 || secondDigit == 7))
        {
            printf("AMEX\n");
        }
        //...or if master card...
        else if (digits == 16 && firstDigit == 5 && (secondDigit > 0 && secondDigit < 6))
        {
            printf("MASTERCARD\n");
        }
        //...or if visa...
        else if ((digits == 16 || digits == 13) && firstDigit == 4)
        {
            //anything else means the card is invalid
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}

//returns the number to be added to fancy sum based on digit inputted
int fancy(int num)
{
    //if the number is single digit even after *2, simply return the single digit product
    if (num < 5)
    {
        return num * 2;
    }
    //otherwise, return the sum of the digits of the product with 2
    else
    {
        return 1 + ((num * 2) % 10);
    }
}