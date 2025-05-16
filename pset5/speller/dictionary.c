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
} node;

// Choose number of buckets in hash table
const unsigned int N = 65536; // Example size, can be tuned

// Hash table
node *table[N];

// Word counter
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Simple hash function: sum of lowercase ASCII values modulo N
    unsigned long hash_value = 0;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        hash_value += tolower(word[i]);
    }
    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Initialize hash table buckets to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Buffer for reading words
    char word_buffer[LENGTH + 1];

    // Read words from dictionary
    while (fscanf(file, "%s", word_buffer) == 1)
    {
        // Create a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            // Ideally, unload already loaded words here, but for simplicity:
            return false;
        }

        // Copy word into node
        strcpy(new_node->word, word_buffer);

        // Hash word to get index
        int index = hash(word_buffer);

        // Insert node into hash table at that index
        new_node->next = table[index];
        table[index] = new_node;

        // Increment word count
        word_count++;
    }

    // Check for errors during reading (excluding EOF)
    if (ferror(file))
    {
        fclose(file);
        unload(); // Clean up potentially partially loaded dictionary
        return false;
    }

    // Close dictionary file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        // Optional: Set table[i] to NULL after freeing list
        table[i] = NULL;
    }
    // Reset word count if desired, though not strictly necessary
    // word_count = 0;
    return true;
}
