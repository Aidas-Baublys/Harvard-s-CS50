#include <cs50.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text, int text_len);
int count_words(string text, int text_len);
int count_sentences(string text, int text_len);

int main(void)
{
    string text;
    int text_len;
    do
    {
        text = get_string("Text: ");
        text_len = strlen(text);
    }
    while (text_len == 0);

    int letters = count_letters(text, text_len);
    int words = count_words(text, text_len);
    int sentences = count_sentences(text, text_len);

    float letters_per_word = (float)letters / words * 100;
    float sentences_per_word = (float)sentences / words * 100;
    float level = 0.0588 * letters_per_word - 0.296 * sentences_per_word - 15.8;

    if (level < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else if (level < 16)
    {
        printf("Grade %0.f\n", level);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int count_letters(string text, int text_len)
{
    int sum = 0;
    for (int i = 0; i < text_len; i++)
    {
        if ((text[i] > 64 && text[i] < 91) || (text[i] > 96 && text[i] < 123))
        {
            sum++;
        }
    }

    return sum;
}

int count_words(string text, int text_len)
{
    int sum = 0;
    for (int i = 0; i < text_len; i++)
    {
        if (text[i] == 32)
        {
            sum++;
        }
    }

    // Count the last word that has no space after it.
    return ++sum;
}

int count_sentences(string text, int text_len)
{
    int sum = 0;
    for (int i = 0; i < text_len; i++)
    {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            sum++;
        }
    }

    return sum;
}
