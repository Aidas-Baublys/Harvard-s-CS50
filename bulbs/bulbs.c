#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define BITS_IN_BYTE 8

void print_bulb(int bit);

int main(void)
{
    string msg = get_string("Message: ");
    int msg_len = strlen(msg);

    if (msg_len == 0)
    {
        printf("Message has to be at least one simbol long.\n");
        return 0;
    }

    for (int i = 0; i < msg_len; i++)
    {
        int byte[BITS_IN_BYTE];
        int ch = msg[i];

        for (int k = 0; k < BITS_IN_BYTE; k++)
        {
            byte[BITS_IN_BYTE - 1 - k] = ch % 2;
            ch /= 2;
        }

        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            print_bulb(byte[j]);
        }

        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
