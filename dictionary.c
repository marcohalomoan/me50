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
const unsigned int N = 65536;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(char *word)
{
    // alter the argument to char to make easy to edit
    int index = hash(word); // the index
    node *checker = table[index]; // the pointer to check
    while(checker != NULL) // null means reaching the end
    {
        if(strcasecmp(checker->word, word) == 0) // zero means equal
        {
            return true;
        }
        checker = checker->next; // continue checking if can't find
    }
    return false;
}

// Hashes word to a number
// https://cs50.stackexchange.com/questions/37209/pset5-speller-hash-function
// with a bit of alterning the ascii code
unsigned int hash(char *word)
{
    // alter the argument to char to make easy to edit
    unsigned int hash_value = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (word[i] > 64 && word[i] < 91)
        {
            word[i] += 32;
            hash_value = (hash_value << 2) ^ word[i];
            word[i] -= 32;
            // convert to lower case then return it so it will print the original
        }
        else
        {
            hash_value = (hash_value << 2) ^ word[i];
        }
    }
    return hash_value % N; //N is size of hashtable
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char *word = malloc((LENGTH + 1) * sizeof(char)); // allocate empty string
    FILE *f = fopen(dictionary, "r"); // open the file
    if (f == NULL) // file does not exist
    {
        printf("File can not be opened\n");
        return false;
    }
    while(fscanf(f, "%s", word) != EOF) // EOF is the end of the file
    {
        int index = hash(word); // which linked list we gonna put
        node *n = malloc(sizeof(node)); // allocate a node for linked list
        if (n == NULL) // run out of memory
        {
            unload();
            return false;
        }
        strcpy(n->word, word); // copy the string to the node
        n->next = table[index]; // point at whatever table is pointing at
        table[index] = n; // table point at new node
        count_size++; // count the number of words
    }
    fclose(f); // close file
    free(word); // free the string 'word'
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
        if(table[i] != NULL) // nothing inside the table
        {
            node *checker = table[i]; // point to whatever table is pointing at
            node *deleter = table[i];
            while(checker != NULL) // NULL is the end
            {
                checker = checker->next; // continue
                free(deleter); // free whatever deleter pointing at
                deleter = checker; // go after checker
            }
        }
    }
    return true;
}
