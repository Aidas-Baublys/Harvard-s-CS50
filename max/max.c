#include <cs50.h>
#include <stdio.h>

int max(int array[], int arr_len);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
}

int max(int array[], int arr_len)
{
    int max = array[0];
    for (int i = 1; i < arr_len; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }

    return max;
}
