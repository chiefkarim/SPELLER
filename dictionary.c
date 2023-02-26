// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
// Size of dictionary
unsigned int Dictionarysize=0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);

     node *currentt=table[index];
         while(currentt->next != NULL && strcasecmp(currentt->word,word) != 0)
    {
        currentt=currentt->next;
    }
    if(strcasecmp(currentt->word,word) == 0)
    {

        return true;
    }


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
    // TODO
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Couldn't open file!");
        return false;
    }

    // Reading file
    char word[LENGTH + 1];


    while (fscanf(file, "%s", word) != EOF)
    {
        node *current = malloc(sizeof(node));
       strcpy(current->word, word);
        current->word[strlen(word)]='\0';
        int index = hash(word);
        current->next = NULL;
        current->next = table[index];
        table[index] = current;

        //Reseting word
        for(int i=0;i<LENGTH+1;i++){
            word[i]='\0';
        }
        Dictionarysize++;

    }

fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
   // printf("%u\n",Dictionarysize);
    return Dictionarysize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
   // TODO

    for(int i = 0; i < N; i++ )
    {
        node *temp=table[i];

        while(temp->next != NULL){
           node *currents=temp->next;
            free(temp);
            temp=currents;
                    }
                  free(temp);
    }

    return true;
}
