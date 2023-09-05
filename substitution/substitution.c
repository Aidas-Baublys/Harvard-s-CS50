#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define ABC_LEN 26

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    if (strlen(key) != ABC_LEN)
    {
        printf("Key must contain 26 unique abc characters.\n");
        return 1;
    }

    for (int i = 0; i < ABC_LEN; i++)
    {
        char caps_key = toupper(key[i]);
        if (caps_key < 65 || caps_key > 90)
        {
            printf("Key must contain 26 unique abc characters.\n");
            return 1;
        }
    }

    char letters[ABC_LEN];

    for (int i = 0; i < ABC_LEN; i++)
    {
        char current = toupper(key[i]);
        for (int j = i + 1; j < ABC_LEN; j++)
        {
            if (current == toupper(key[j]))
            {
                printf("Key must contain 26 unique abc characters.\n");
                return 1;
            }
        }

        letters[i] = current;
    }

    string plain_text = "";
    int plain_text_len = 0;

    do
    {
        plain_text = get_string("plaintext: ");
        plain_text_len = strlen(plain_text);
    }
    while (plain_text_len < 1);

    char cipher_text[plain_text_len];

    for (int i = 0; i < plain_text_len; i++)
    {
        char letter = plain_text[i];
        cipher_text[i] = letter;
        if (letter > 64 && letter < 91)
        {
            cipher_text[i] = letters[letter - 65];
        }
        if (letter > 96 && letter < 123)
        {
            cipher_text[i] = tolower(letters[letter - 97]);
        }
    }

    printf("ciphertext: ");
    for (int i = 0; i < plain_text_len; i++)
    {
        printf("%c", cipher_text[i]);
    }
    printf("\n");
}
