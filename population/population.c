#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("\n");
    printf("Welcome to llama breader!!!\n");
    printf("We make more llamas!\n");
    printf("\n");

    int startPop;

    while (true)
    {
        startPop = get_int("Please provide a positive full number for llama start population: ");

        if (startPop >= 9)
        {
            break;
        }

        printf("Start population should be greater or equal to 9. Trust me.\n");
    }

    int endPop;

    while (true)
    {
        endPop = get_int("Please provide a positive full number for llama end population: ");

        if (endPop >= startPop)
        {
            break;
        }

        printf("End population should be greater or equal to start population (%i).\n", startPop);
    }

    int years = 0;

    while (startPop < endPop)
    {
        startPop += (startPop / 3) - (startPop / 4);
        years++;
    }

    printf("Years: %i\n", years);
}
