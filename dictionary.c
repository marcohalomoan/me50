// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Keep track of how many words in the dictionary
int count_size = 0;

// Number of buckets in hash table
const unsigned int N = 150000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    node *checker = table[index];
    while(checker->next != NULL)
    {
        if(strcasecmp(word, checker->word) == 0)
        {
            return true;
        }
        checker = checker->next;
    }
    return false;
}

// Hashes word to a number
// https://stackoverflow.com/questions/7666509/hash-function-for-string
// http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char *word = NULL;
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        printf("File can not be opened\n");
        return false;
    }
    while(fscanf(f, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == 0)
        {
            unload();
            return false;
        }
        strcpy(n->word, word);
        int index = hash(word);
        n->next = table[index];
        table[index] = n;
        count_size++;
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        node *checker = table[i];
        node *deleter = table[i];
        while(checker->next != NULL)
        {
            checker = checker->next;
            free(deleter);
            deleter = checker;
        }
    }
    return true;
}
