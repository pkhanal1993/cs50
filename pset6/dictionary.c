/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


// create an array of node pointers ( a hash table basically) "global variable"
    node* first_l[27];    

// global variable to count the words in a dictionary
    unsigned int total_words = 0;
    
    
// clear function prototype
node* clear(node* node);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // get ready to check the word
    char c = word[0];      int hash;   node* next;
    
    for(int i = 0; c != '\0'; i++)
    {
        
        // calculate hash value
        if (c == '\'')
        {
            hash = 26;
        }
        
        else
        {
            hash = tolower(c) - 'a';
        }
        
        // check if it's the first letter and update next pointer
        if ( i == 0)
        {
            if (first_l[hash] == NULL)
            {
                return false;
            }
            next =  first_l[hash];
        }
        
        else
        {
            if (next -> next[hash]!= NULL)
            {   
                next = next -> next[hash];
            }
            else
            {
                return false;
            }
            
        }
        
        // update c
        c = word[i+1];
        
        if ( c == '\0' && next -> val == '1' )
        {
            return true;
        }
        
        
        
    }      
    
    
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // initialize first_l[27] to NULL
    for(int i = 0; i < 27; i++)
        first_l[i] = NULL;
    
    // open the file
    FILE* file = fopen(dictionary, "r");
    
    // get ready to load the dictionary into memory
    char c = getc(file);    int let_index = 0,  hash = 0;    node* prev;
    
    
    
    while(c != EOF)
    {
        // prepare for loading a new word
        let_index = 0;      prev = NULL;
        
        while(c != '\n')
        {
               // calculate hash value
               
               if ( c == '\'')
               {
                    hash = 26;
               }
               
               else
               {
                    hash = tolower(c) - 'a';
               }
               
               
               // check if it's the first word with that first letter
               if (first_l[hash] == NULL && let_index == 0)
               {
                    // create a new node
                    node* new_node = malloc(sizeof(node));
                    if ( new_node == NULL)
                    {
                        return false;
                    }
                    
                    // intialize all the pointers in new_node -> next[27] to NULL
                    for(int i = 0; i < 27; i++)
                        new_node -> next[i] = NULL;
                        
                        
                        
                    
                    
                    // update the value of first_l[hash]
                    first_l[hash] = new_node;
                    prev = new_node;
                    
               }
               else
               {
                    if (let_index == 0)
                    {
                        prev = first_l[hash];
                        
                    }
                    
                    else
                    {
                        if ( prev -> next[hash] == NULL)
                        {
                        
                            // create a new_node
                            node* new_node = malloc(sizeof(node));
                            
                            
                            
                            prev -> next[hash] = new_node;
                            prev = new_node;
                            
                        }
                        else
                        {
                            prev = prev -> next[hash];
                        }
                    
                    } 
                    
               }
               let_index++;
               c = getc(file);
        }
        c = getc(file);
        
        // put a flag-value to ensure it's a word in dictionary
        if ( prev != NULL)
        {
            prev -> val = '1'; 
        }
        
        total_words++;
    }
    
    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // return the number of words in dictionary
    return total_words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // unload the dictionary
    for(int j = 0; j < 27; j++)
    {
        if ( first_l[j] != NULL)
        {
            
            
            clear(first_l[j]);     
        } 
    }
    
    return true;
}


/**
 * Free each node from memory. Return node pointer
 */
node* clear(node* node)
{
    
for(int i = 0; i < 27; i++)
{
    if ( node -> next[i] != NULL)
    {
        clear(node -> next[i]);
    }
}

free(node);

return NULL;
}
