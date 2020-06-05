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
const unsigned int N = 200000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    if (table[index] == NULL)
    {
        return false;
    }
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
// https://cs50.stackexchange.com/questions/37209/pset5-speller-hash-function
unsigned int hash(const char *word)
{
    unsigned int hash_value = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash_value = (hash_value << 2) ^ word[i];
    }
    return hash_value % N; // N is size of hashtable
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char *word = malloc((LENGTH + 1) * sizeof(char));
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        printf("File can not be opened\n");
        return false;
    }
    while(fscanf(f, "%s", word) != EOF)
    {
        int index = hash(word);
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        n->next = table[index];
        table[index] = n;
        printf("%s\n",table[index]->word);
        count_size++;
    }
    free(word);
    fclose(f);
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
