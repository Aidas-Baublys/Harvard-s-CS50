#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string arg = argv[1];
    int arg_len = strlen(arg);

    for (int i = 0; i < arg_len; i++)
    {
        char ch = arg[i];
        if (ch < 48 || ch > 57)
        {
            printf("Key must a possitibe integer.\n");
            return 1;
        }
    }

    int key = atoi(arg);

    if (key < 1)
    {
        printf("Key must a possitibe integer.\n");
        return 1;
    }

    string plain_text = "";
    int plain_text_len = 0;

    do
    {
        plain_text = get_string("plaintext: ");
        plain_text_len = strlen(plain_text);
    }
    while (plain_text_len == 0);

    char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char cipher_text[plain_text_len];

    for (int i = 0; i < plain_text_len; i++)
    {
        char letter = plain_text[i];
        cipher_text[i] = letter;
        if (letter > 96 && letter < 123)
        {
            int index = letter - 97 + key;
            while (index > 25)
            {
                index -= 26;
            }
            cipher_text[i] = letters[index];
        }

        if (letter > 64 && letter < 91)
        {
            int index = letter - 65 + key;
            while (index > 25)
            {
                index -= 26;
            }
            cipher_text[i] = toupper(letters[index]);
        }
    }

    printf("ciphertext: ");
    for (int i = 0; i < plain_text_len; i++)
    {
        printf("%c", cipher_text[i]);
    }
    printf("\n");
}