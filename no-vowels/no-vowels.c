#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string replace(string word);

int main(int argc, string argv[])
{
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }

    printf("%s\n", replace(argv[1]));
}

string replace(string word)
{
    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        switch (tolower(word[i]))
        {
            case 97:
                word[i] = 54;
                break;
            case 101:
                word[i] = 51;
                break;
            case 105:
                word[i] = 49;
                break;
            case 111:
                word[i] = 48;
                break;
        }
    }

    return word;
}