/*
 * David Taylor
 * Project 2
 * This file contains functions that allow for the creation and manipulation of an unsorted
 * set,namely deleting the set, finding an element in the set, checking if an element exists in a
 * set, adding an element to a set, and removing an element from a set.
 */

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "set.h"
#include <string.h>

/*
 * Definition of the structure "set".  This has a Big O complexity of O(3)
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
    sp = malloc(sizeof(SET));       //Memory allocation for the set
    assert(sp != NULL);             //Ensures the set was properly aloocated memory
    sp->count = 0;                  //Sets inital value of elements in array to 0
    sp->length = maxElts;           //Sets the length of the array to the inputed max amount of elements
    sp->elts = malloc(sizeof(char*) * maxElts);     //Creates a dynamic array for the set
    assert(sp->elts != NULL);       //Ensures the array was properly initialized
    return sp;
}

/*
 This function destroys a set, freeing the memory it took up. It does so by first freeing the elements in each index of the set's array, then freeing array, before finally freeing the set pointer. This has a Big O complexity of O(n)
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
 This Function returns the number of elements in the inputted set's array. It has a Bid O complexity of O(1)
 */
int numElements(SET *sp) {
    return sp->count;
}

/*
 This function searches a set's array for a given string.  The searched used is a sequential search.  If the string is found, its postion is returned.  If it is not found, -1 is returned.  A set and a string are required as input for the function.  Its Big O complexity is O(n).
 */
int findElement(SET *sp, char *elt) {
    assert(sp != NULL);                     //Ensures the set is not empty
    int i;
    for(i = 0; i < sp->count; i++)          //Loops through the array
        if(strcmp(sp->elts[i], elt) == 0)   //Checks if the string at the current index and the string that is being searched for are equal
            return i;                       //returns the position of the found string
    return -1;                              //returns if string is not found
}

/*
This function returns whether or not a given string exists in a given set's array of strings.  It does this by calling on the findElement Function.  It requires a set and a string to search for as input.  Its Big O complexity is O(n).
*/
bool hasElement(SET *sp, char *elt)
{
    assert(sp != NULL);             //Ensures the set is not empty
    if(findElement(sp, elt) > -1)   //Checks if the string exists in the set's array
    {
        return true;
    }
    return false;
    
}

/*
 This function adds a given string into the array of a given set. IT calls upon findElement in order to ensure the given string does not already exist in the array. It places the given string at the first open slot in the array at the end. This function requires a set and a string as inputs.  The big O complexity of this function is O(n).
 */
bool addElement(SET *sp, char *elt)
{
    assert(sp != NULL);                         //Ensures the set is not empty
    if(hasElement(sp, elt) == false)            //Checks if the given string already exists in the array
    {
        if(sp->count < sp->length) {            //Checks if the array is full
            sp->elts[sp->count] = strdup(elt);  //Copies the given string into the first open slot
            sp->count++;                        //Adds one to the count of elements in the array
            return true;
        }
    }
    return false;
}

/*
 This function removes a given string from the sorted array of a given set. It does this by freeing the position of the given string, then placing the last element in the array in the former position of the given string, and setting the former position of the last element in the array to Null. It calls upon findElement to check if the string exists in the array. This function requires a set and a string as inputs.  The big O complexity for this function is O(n)
 */
bool removeElement(SET *sp, char *elt)
{
    assert(sp != NULL);                         //Ensures the set isn't empty
    if(findElement(sp, elt) > -1)               //Checks if the given string exists in the array
    {
        int loc = findElement(sp, elt);         //Sets loc as the position of the given string
        int lastIndex = sp->count - 1;          //Sets lastIndex as the last element in the array
        free(sp->elts[loc]);                    //Frees the position of the given string
        sp->elts[loc] = sp->elts[lastIndex];    //Moves the last element of the array to the position of the given string
        sp->elts[lastIndex] = NULL;             //Sets the former position of the last element of the array to Null
        sp->count--;                            //Removes 1 from the total number of elements in the array
        return true;
    }
    return false;
}




