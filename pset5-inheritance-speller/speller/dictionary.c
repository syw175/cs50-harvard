/*
 * Filename: speller.c
 *
 * Description: Implements a dictionary's functionality
 *
 *
 * Author: Steven Wong
 * Date: July 18, 2022
 */


#include <ctype.h>
#include <stdbool.h>  // for boolean
#include <stdlib.h>  // for file
#include <stdio.h> // for input output
#include <string.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
unsigned int dictionaryCount = 0;


// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file 
    FILE *fileToRead = fopen(dictionary, "r");

    // Check if file open was successful, else, return false 
    if (fileToRead == NULL) { 
        return false;
    }

    // Buffer for a word 
    char currentWord[LENGTH+1];

    // While the current word is not EOF, 
    while (fscanf(fileToRead, "%s", currentWord) != EOF) { 
        // if (currentWord == NULL) { 
        //     return false;
        // }
        
        // Create a new node for the current word 
        node *newNode = malloc(sizeof(node)); 

        // Check if memory allocation failed
        if (newNode == NULL) { 
            return false;
        }

        // Copy the current word into a new node and hash it
        strcpy(newNode->word, currentWord);
        newNode->next = NULL;

        // Hash the word 
        int indexForNewNode = hash(newNode->word);

        // Insert the new node at the index value given by the hash function
        node *temp = table[indexForNewNode]->next;
        table[indexForNewNode] = newNode;
        newNode->next = temp;
        dictionaryCount++;
    }
    fclose(fileToRead);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // return dictionaryCount;
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}


