// pset5 was all about data structures, learning how to create, add to, search through, and eliminate linked lists. I wrote each of these functions to be called in "speller.c"

// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// number of words in dictionary
int dict_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // hash word to obtain a hash value
    int head = hash(word);
    node *cursor = table[head];

    // traverse linked list, look for the word (strcasecmp)
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) != 0) // check the word
        {
            cursor = cursor->next; // not a match, move on
        }
        else
        {
            return true; // is a match, return
        }
    }

    return false;
}

// Hashes word to a number - output is between 0 and N - 1
unsigned int hash(const char *word)
{
    int index;

    // simple has based on first letter of word
    index = tolower(word[0]) - 97;

    return index;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not load %s.\n", dictionary);
        return false;
    }

    // set up empty hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }


    // read strings one at a time
    char word[LENGTH + 1];
    node *n;

    while (fscanf(dict, "%s", word) != EOF)
    {
        // create a new node for each word, remember to check if return value is NULL
        n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            return false;
        }

        // initialize value field, 'next' field
        strcpy(n->word, word);
        n->next = NULL;

        // hash word to obtain a hash value
        int head = hash(word);

        // insert node into hash table at that location
        if (&table[head] == NULL)      // if table[head] not pointing to anything
        {
            table[head] = n;
        }

        else
        {
            n->next = table[head];
            table[head] = n;
        }

        dict_count++;
    }

    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dict_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor;
    // loop through full index of hashtable
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];

        if (cursor == NULL)
        {
            free(cursor);
        }

        else
        {
            while (cursor->next != NULL)
            {
                node *tmp = cursor;
                cursor = cursor->next;
                free(tmp);
            }
            free(cursor);
        }

        if (N - i == 1)     // check if moved through entire arry
        {
            return true;
        }
    }
    return false;
}
