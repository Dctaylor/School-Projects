/*
 David Taylor
 Project 2
 
 This file contains functions that allow for the creation and manipulation of a sorted set, namely
 deleting the set, finding an element in the set, checking if an elemnt exists in a set,
 adding an element to a set, and removing an element from a set.
 */

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "set.h"
#include <string.h>

/*
 Definition of the structure "set".  This has a Big O complexity of O(3)
 */
struct set
{
    int count;      //# of elements in the array
    int length;     //Length of the array
    char **elts;    //An array of strings
};

/*
 This function creates a Set, which contains an array of strings.
 A value for the maximum number of elements in the array is required as input.
 Memory is allocated for the set, the calues for the length and number of
 elements in the array is initilized, and the array itself is created.
 This has a Big O complexity of O(1);
 */
SET *createSet(int maxElts)
{
    SET *sp;
    sp = malloc(sizeof(SET));                       //Memory allocation for the set
    assert(sp != NULL);                             //Ensures the set was properly aloocated memory
    sp->count = 0;                                  //Sets inital value of elements in array to 0
    sp->length = maxElts;                           //Sets the length of the array to the inputed max amount of elements
    sp->elts = malloc(sizeof(char*) * maxElts);     //Creates a dynamic array for the set
    assert(sp->elts != NULL);                       //Ensures the array was properly initialized
    return sp;
}

/*
 This function destroys a set, freeing the memory it took up. It does so by first freeing the array of characters in each slot of the array, then freeing the array, before finally freeing the set pointer. It takes a set as input. This has a Big O complexity of O(n)
 */
void destroySet(SET *sp)
{
    assert(sp != NULL);             //Ensures the set is not empty
    int i;
    for(i = 0; i < sp->count; i++)  //Loops through the array index
        if(sp->elts[i] != NULL)     //Checks if the current index is empty or not
            free(sp->elts[i]);      //Frees the current index of the array
    
    free(sp->elts);                 //Frees the array
    free(sp);                       //Frees the set
}

/*
 This Function returns the number of elements in a set's array. It takes a set as input. It has a Big O complexity of O(1)
 */
int numElements(SET *sp)
{
    return sp->count;
}

/*
 This Function checks to see if a string exists in a set's sorted array, returning false and the position the string that was searched for would go if it were to be placed into the array if the string was not found, or true and the position of the element if the element was found. A set, a string, and a boolean are required as input.  The search is done through binary search. It's Big O complexity is O(logn).
 */
int findElement(SET *sp, char *elt, bool *found)
{
    assert(sp != NULL);                         //Ensures the set is not empty
    int lo, hi, mid, diff;
    lo = 0;                                     //Initializes the low value of the search range at 0
    hi = sp->count - 1;                         //Initializes the high value of the search range at the number of elements in the array minus 1
    while(lo <= hi)                             //While loop that searches the array until the string is found or lo and hi are equal
    {
        mid = (lo + hi)/2;                      //Sets the mid vaulue, the position we will search each time
        diff = strcmp(elt, sp->elts[mid]);      //sets diff, which tells us if the string we want is lower or higher alphabetically
        if(diff < 0)                            //Fires if Lower alphabetically
            hi = mid - 1;
        else if(diff > 0)                       //Fires if higher alphabetically
            lo = mid + 1;
        else                                    //Fires if the string we are searching for and the string located at the index we are searching are the same
        {
            *found = true;
            return mid;
        }
    }
    *found = false;
    return lo;
}

/*
 This function returns whether or not a given string exists in a given set's array of strings.  It does this by calling on the findElement Function.  It requires a set and a string to search for as input.  Its Big O complexity is O(log n).
 */
bool hasElement(SET *sp, char *elt)
{
    assert(sp != NULL);           //Ensures the set is not empty
    bool f;
    findElement(sp, elt, &f);    //Calls findElement to set f
    return f;
    
}

/*
 This function adds a given string into the sorted array of a given set in its proper place, keeping the array sorted.  It does this by calling on findElement to learn where the given string should go, then moving each element of the array after its needed position to the right one in order to keep the array properly sorted.  This function requires a set and a string as inputs.  The big O complexity of this function is O(log n).
 */
bool addElement(SET *sp, char *elt)
{
    assert(sp != NULL);                             //Ensures the set is not empty
    bool f;
    int pos;
    pos = findElement(sp, elt, &f);                 //Sets pos as the position of the found string
    if(f == false)                                  //Fires if the string was not found in the set's array
    {
        if(sp->count < sp->length)                  //Checks if the array is full
        {
            int i;
            for(int i = sp->count; i > pos; i--)    //Loops through the array
                sp->elts[i] = sp->elts[i - 1];      //Moves elements in the array 1 to the left in order to open up the needed position for the given string
            sp->elts[pos] = strdup(elt);            //Places the given string in its position
            assert(sp->elts[pos] != NULL);          //Ensures the string was properly placed
            sp->count++;                            //Adds 1 to the total number of elements in the array
            return true;
        }
    }
    return false;
}

/*
 This function removes a given string from the sorted array of a given set. After removing the string, it moves all elements that came after its position one to the left in order to maintain the proper order of the array.  It calls upon findElement to find the position of the given string. This function requires a set and a string as inputs.  The big O complexity for this function is O(log n)
 */
bool removeElement(SET *sp, char *elt)
{
    assert(sp != NULL);                         //Ensures the set isn't empty
    bool f;
    int pos;
    pos = findElement(sp, elt, &f);             //Sets pos as the position of the given string
    if(f == true)                               //Fires if the string is found in the array
    {
        free(sp->elts[pos]);                    //Frees the index of the given string
        int i;
        for(i = pos + 1; i < sp->count; i++)    //Loops through the array from the position of the given string onward
            sp->elts[i-1] = sp->elts[i];        //Moves the current index of the loops one to the left
        sp->count--;                            //Removes 1 from the total number of elements in the array
        return true;
    }
    return false;
}




