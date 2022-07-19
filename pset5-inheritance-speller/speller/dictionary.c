/*
 * Filename: speller.c
 *
 * Description: Implements a dictionary's functionality
 *
 *
 * Author: Steven Wong
 * Date: July 19, 2022
 */


#include <ctype.h>
#include <stdbool.h>  // for boolean
#include <stdlib.h>  // for file
#include <stdio.h> // for input output
#include <string.h>
#include <strings.h> // for strcasecmp

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
    // Hash the word
    int indexToCheck = hash(word);
    // Get the head of linkedlist element in the hash table
    node *currentNode = table[indexToCheck];

    // While the current node is not NULL
    while (currentNode != NULL) {
        // If the word is found, return true
        if (strcasecmp(word, currentNode->word) == 0) {
            return true;
        }
        // Otherwise, move to the next node
        currentNode = currentNode->next;
    }
    // If the word is not found, return false
    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';
    unsigned long total = 0;
    for (int i = 0; i < strlen(word); i++) {
        total += tolower(word[i]);
    }

    return total % N;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *fileToRead = fopen(dictionary, "r");

    // Check if file is open, if not, return false
    if (fileToRead == NULL) {
        return false;
    }

    // Buffer for reading in words from file
    char currentWord[LENGTH+1];

    // Loop through file and add words to hash table
    while (fscanf(fileToRead, "%s", currentWord) != EOF) {

        // Create new node for current word
        node *newNode = malloc(sizeof(node));

        // Check if node is correctly allocated, if not, return false
        if (newNode == NULL) {
            return false;
        }

        // Copy word to new node
        strcpy(newNode->word, currentWord);

        // Get hash value for current word
        int indexForNewNode = hash(newNode->word);

        // Set new node's next to the head of the linkedlist in the hash table at indexForNewNode
        newNode->next = table[indexForNewNode];
        // Set current node to head of linked list at index
        table[indexForNewNode] = newNode;
        // Increment dictionary count
        dictionaryCount++;
    }

    // Close file and return true
    fclose(fileToRead);
    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return dictionary count
    if (dictionaryCount > 0) {
        return dictionaryCount;
    }
    return 0;
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop through hash table
    for (int i = 0; i < N; i++) {
        // Get the current node
        node *current = table[i];

        // While current node is not NULL
        while (current != NULL) {
            // Get the next node
            node *next = current->next;
            // Free the current node
            free(current);
            // Set current node to next node
            current = next;
        }
    }
    // Return true
    return true;
}


