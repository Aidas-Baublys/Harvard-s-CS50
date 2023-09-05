#include "dictionary.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];
int word_count = 0;

bool search(node *bucket, const char *word);
void free_next(node *bucket);

bool search(node *bucket, const char *word)
{
    if (bucket == NULL)
    {
        return false;
    }
    if (strcasecmp(bucket->word, word) == 0)
    {
        return true;
    }
    if (bucket->next == NULL)
    {
        return false;
    };
    return search(bucket->next, word);
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int h = hash(word);
    return search(table[h], word);
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int total = 0;
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        total += (toupper(word[i]) * tolower(word[i]) * i);
    }

    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(f, "%s", word) != EOF)
    {
        node *w = malloc(sizeof(node));
        if (w == NULL)
        {
            return false;
        }

        strcpy(w->word, word);
        unsigned int h = hash(word);
        if (table[h] == NULL)
        {
            w->next = NULL;
            table[h] = w;
        }
        else
        {
            w->next = table[h]->next;
            table[h]->next = w;
        }
        word_count++;
    }

    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

void free_next(node *bucket)
{
    if (bucket->next != NULL)
    {
        free_next(bucket->next);
    }
    free(bucket);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            free_next(table[i]);
        }
    }
    return true;
}