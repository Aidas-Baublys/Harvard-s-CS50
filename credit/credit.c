#include <cs50.h>
#include <stdio.h>

int get_long_len(long value);

int main(void)
{
    long cardNum = 0;
    do
    {
        cardNum = get_long("Number: ");
    }
    while (cardNum <= 0);

    int cardNumLen = get_long_len(cardNum);

    if (cardNumLen != 15 && cardNumLen != 16 && cardNumLen != 13)
    {
        printf("INVALID\n");
        return 0;
    }

    long cardNumDigits = cardNum;
    int checkSum = 0;

    for (int i = 1; cardNumDigits > 0; i++)
    {
        int digit = cardNumDigits % 10;

        if (i % 2 != 0)
        {
            checkSum += digit;
        }
        else
        {
            int digitDigit = digit * 2;
            if (digitDigit > 9)
            {
                checkSum += digitDigit % 10;
                checkSum += digitDigit /= 10;
            }
            else
            {
                checkSum += digitDigit;
            }
        }

        cardNumDigits /= 10;
    }

    if (checkSum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    if (cardNumLen == 15)
    {
        long firstDigits = cardNum / 10000000000000;

        if (firstDigits == 34 || firstDigits == 37)
        {
            printf("AMEX\n");
            return 0;
        }
    }

    if (cardNumLen == 16)
    {
        long firstDigits = cardNum / 100000000000000;

        if (firstDigits == 51 || firstDigits == 52 || firstDigits == 53 || firstDigits == 54 || firstDigits == 55)
        {
            printf("MASTERCARD\n");
            return 0;
        }

        firstDigits = cardNum / 1000000000000000;

        if (firstDigits == 4)
        {
            printf("VISA\n");
            return 0;
        }
    }

    if (cardNumLen == 13)
    {
        long firstDigits = cardNum / 1000000000000;

        if (firstDigits == 4)
        {
            printf("VISA\n");
            return 0;
        }
    }

    printf("INVALID\n");
    return 0;
}

int get_long_len(long value)
{
    int len = 1;
    while (value > 9)
    {
        len++;
        value /= 10;
    }
    return len;
}