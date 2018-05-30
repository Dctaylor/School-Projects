/*
 David Taylor
 Project 3

 This file contains functions that allow for the creation and manipulation of a set using hashing, namely deleting the set, finding an element in the set, checking if an element exists in the set, adding an element to the set, and removing an element from a set. 
*/

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "set.h"
#include <string.h>

/*
 * This function hashes a given string, assigning it a unique number. Big O complexity: Best case of O(1). Worst Case
 */

unsigned hashString(char *s)
{
    unsigned hash = 0;
    
    while(*s != '\0')
        hash = 31 * hash + *s ++;
    
    return hash;
}

/*
 * Enumerated Type to indicate that status of an array slot
 */

typedef enum
{
    Empty,
    Filled,
    Deleted
} Flag;

/*
 * Defintion of the structure "set".
 */

struct set
{
    int count;
    int length;
    char **elts;
    Flag *flags;
};

/*
 * Description: Creates and initializes a set, assigning memory for its array of strings and setting the status of each array index to Empty using an array of Flags.
 *
 * Complexity: Expected and Worst: O(n)
 */

SET *createSet(int maxElts)
{
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->elts = malloc(sizeof(char*) * maxElts);
    assert(sp->elts != NULL);
    
    sp->flags = malloc(sizeof(Flag) * maxElts);
    assert(sp->flags != NULL);
    int i;
    for(i = 0; i < maxElts; i++)
    {
        sp->flags[i] = Empty;
    }
    
    return sp;
}

/*
 * Description: Destroys a given set, freeing its allocated memory.  Frees each Filled index in the array, then the array itself, before finally freeing the set.
 *
 * Complexity: Expected and Worst: O(n).
 */

void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;
    for(i = 0; i < sp->length; i++)
        if(sp->elts[i] != NULL && sp->flags[i] == Filled)
                free(sp->elts[i]);
    
    free(sp->elts);
    
    free(sp);
}

/*
 * Desctiption: Returns the number of elements in the sert's array.
 *
 * Complexity: Expected and Worst: O(1).
 */

int numElements(SET *sp)
{
    return sp->count;
}

/*
 * Description: Searches a set's array of string for a given string.  Starts at the expected hash location of the given string, and if not found, indexes through using linear probing until the string is found or an index with Flag status Empty is found.  Keeps track of first index found with a Flag status of Deleted. If found, the location is returned and a boolean is set to true. If not found, the location it would go is returned and a boolean is set to false.
 *
 * Complexity: Expected: O(1); Worst: O(n)
 */

int findElement(SET *sp, char *elt, bool *found)
{
    assert(sp != NULL && elt != NULL);
    int i;
    int loc;
    int firstDeleted;
    firstDeleted = -1;
    Flag locFlag;
    *found = false;
    for(i = 0; i < sp->length; i++)
    {
        loc = ((hashString(elt)) + i) % sp->length;
        locFlag = sp->flags[loc];
        
        if(locFlag == Filled && strcmp(elt, sp->elts[loc]) == 0)
        {
            *found = true;
            return loc;
        }
                
        if(locFlag == Deleted && firstDeleted == -1)
        {
            firstDeleted = loc;
        }
        
        if(locFlag == Empty)
        {
            if(firstDeleted != -1)
                return firstDeleted;
            
            return loc;
        }
    }
    
    *found = false;
    return firstDeleted;
}

/*
 * Desctiption: Uses findElement to search a set's array for a given string. Returns true if found or false if not found.
 *
 * Complexity: Expected: O(1); Worst: O(n);
 */

bool hasElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
    bool found;
    findElement(sp, elt, &found);
    return found;
}

/*
 * Desctiption: Uses findElement to check if a given string is in a set's array of strings. If the string is not found, it then adds the given string to the position returned by findElement, adds one to the count of elements in the array, sets the flag status of the index to Filled, and returns true. Returns false otherwise.
 *
 * Complexity: Expected: O(1); Worst O(n)
 */

bool addElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
    int loc;
    bool found;
    loc = findElement(sp, elt, &found);
    if(found == false && loc >= 0)
    {
        if(sp->count <= sp->length)
        {
            sp->elts[loc] = strdup(elt);
            sp->flags[loc] = Filled;
            sp->count++;
            return true;
        }
        return false;
    }
    return false;
}

/*
 * Desctiption: Uses findElement to search a set's array of strings for a given string.  If found, it frees the memory, sets the flag status of the index to Deleted, subtracts 1 from the count of elements in the array, and returns true.  Otherwise it returns false.
 *
 * Complexity: Expected: O(1); Worst: O(n)
 */

bool removeElement(SET *sp, char *elt)
{
    assert(sp != NULL && elt != NULL);
    int loc;
    bool found;
    loc = findElement(sp, elt, &found);
    if(found == true)
    {
        free(sp->elts[loc]);
        sp->flags[loc] = Deleted;
        sp->count--;
        return true;
    }
    return false;
}