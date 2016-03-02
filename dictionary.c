/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

#define MAX_LETTERS 27

typedef struct node
{
    bool isWord;
    struct node* children[MAX_LETTERS];
}
node;

// root node where we have the first letters of each word.

unsigned int wordCount = 0;
static node rootNode = {0};

 /* Returns true if  word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    node* currentNode = &rootNode;
    
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        int index = tolower(word[i]) - 'a';
        if (currentNode->children[index] == NULL)
        {
            return false;
        }
    
        currentNode = currentNode->children[index];
    }

    return currentNode->isWord;
}

/**
 * load helper fuction to load the word into a tree.
 *
 */
void load_word(char* word)
{
    size_t i;
    size_t length = strlen(word);
    
    // keep track of the node
    node* currentNode = &rootNode;
    
    for (i = 0; i < length; i++)
    {
        int index = word[i] - 'a';
        if (currentNode->children[index] == NULL)
        {
            node* newNode = (node *) malloc(sizeof(node));
            currentNode->children[index] = newNode;
        }
        currentNode = currentNode->children[index];
        
    }
    currentNode->isWord = true;
}


/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    // open the dictionary file to read from
    FILE* dictionaryFile = fopen(dictionary, "r");
    
    if (dictionaryFile == NULL)
    {
        printf("Couldn't find dictionary file.\n");
        return false;
    }
    
    char word[LENGTH + 1];
   // node* rootNode = malloc(sizeof(node));
    int currentChar = 0;
    
    
        for (int chr = fgetc(dictionaryFile); chr != EOF; chr = fgetc(dictionaryFile))
        {
            if (chr == '\n')
            {
                word[currentChar] = '\0';
                currentChar = 0;
                
                load_word(word);
                wordCount++;
            }
            else 
            {
                // complete the word until you get to the newline character which indicates a new word.
                word[currentChar] = chr;
                currentChar++;
            }
        }
        return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return wordCount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
void freeNode(node* trieToFree)
{
    
    for (int i = 0; i < MAX_LETTERS; i++)
    {
        if (trieToFree->children[i] != NULL)
        {
            freeNode(trieToFree->children[i]);
            free(trieToFree->children[i]);
        }
    }
}
 
 
bool unload(void)
{
    // TODO
    node* trieToFree = &rootNode;
    
    freeNode(trieToFree);
    return true;
    
}







