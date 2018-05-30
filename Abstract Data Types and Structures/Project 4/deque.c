/*
David Taylor
Project 4

This file creates a double ended queue or deque to hold a circular, doubly linked list  
with a dummy node to help a maze solver keep track of the previous paths it could have
taken if it runs into a wall, allowing it to go back and try other paths when needed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "deque.h"

/*
 Typedef of a doubly linked node
 */
typedef struct node {
    struct node *next;
    struct node *prev;
    int data;
} NODE;

/*
 Definintion of a deque, utalizing a dummy node
 */
struct deque {
    int count;
    NODE *dummy;
};

/*
 Creates a deque, assign its count to 0, assigning the dummy node's next and prev pointers to itself, and its data to 0.  O(1)
 */
DEQUE *createDeque(void)
{
    DEQUE *dp;
    dp = malloc(sizeof(DEQUE));
    assert(dp != NULL);
    dp->count = 0;
    dp->dummy = malloc(sizeof(NODE));
    assert(dp->dummy != NULL);
    dp->dummy->next = dp->dummy;
    dp->dummy->prev = dp->dummy;
    dp->dummy->data = 0;
    return dp;
}

/*
 Frees a deque and its nodes, starting at its dummy node and looping until it reaches the last node, after which it frees the deque itself. O(n)
 */
void destroyDeque(DEQUE *dp)
{
    assert(dp != NULL);
    NODE *del = dp->dummy;
    NODE *temp = del;
    if(dp->count > 0)
    {
        do {
            temp = del->next;
            free(del);
            del = temp;
        } while(del->next != dp->dummy);
    }
    free(del);
    free(dp);
    return;
}

/*
 Returns the number of nodes in a deque. O(1)
 */
int numItems(DEQUE *dp)
{
    return dp->count;
}

/*
 Creates a new node and inserts it at the front of the deque.  Does this by moving dummy's next point to the new node, dummy's former next node's prev pointer to the new node, and the new nodes prev pointer to dummy and its next node to dummy's old next.  Increments count up by 1. O(1)
 */
void addFirst(DEQUE *dp, int x)
{
    assert(dp != NULL);
    NODE *new = malloc(sizeof(NODE));
    new->data = x;
    new->next = dp->dummy->next;
    new->prev = dp->dummy;
    dp->dummy->next = new;
    new->next->prev = new;
    dp->count++;
    return;
}

/*
  Creates a new node and inserts it in the last slot of the deque.  Does this by moving dummy's prev point to the new node, dummy's former prev node's next pointer to the new node, and the new nodes next pointer to dummy and its prev pointer to dummy's old prev.  Increments count up by 1. O(1)
 */
void addLast(DEQUE *dp, int x)
{
    assert(dp != NULL);
    NODE *new = malloc(sizeof(NODE));
    new->data = x;
    new->prev = dp->dummy->prev;
    new->next = dp->dummy;
    dp->dummy->prev = new;
    new->prev->next = new;
    dp->count++;
    return;
}

/*
 Removes the first Node in the deque and returns the data it contained.  Creates a pointer to the node to be deleted, sets dummy's next pointer to the node after the one to be deleted, that nodes prev pointer to dummy, then free's the former first node. O(1)
 */
int removeFirst(DEQUE *dp)
{
    assert(dp != NULL);
    NODE *del;
    int temp;
    del = dp->dummy->next;
    dp->dummy->next = del->next;
    del->next->prev = dp->dummy;
    temp = del->data;
    free(del);
    dp->count--;
    return temp;
    
}

/*
  Removes the last Node in the deque and returns the data it contained.  Creates a pointer to the node to be deleted, sets dummy's prev pointer to the node to be deleted's prev pointer, that nodes next pointer to dummy, then free's the former last node. O(1)
 */
int removeLast(DEQUE *dp)
{
    assert(dp != NULL);
    NODE *del;
    int temp;
    del = dp->dummy->prev;
    del->prev->next = dp->dummy;
    dp->dummy->prev = del->prev;
    temp = del->data;
    free(del);
    dp->count--;
    return temp;
}

/*
 Returns the data of the first node in the deque. O(1)
 */
int getFirst(DEQUE *dp)
{
    return dp->dummy->next->data;
}

/*
 Returns the data of the last node in the deque. O(1)
 */
int getLast(DEQUE *dp)
{
    return dp->dummy->prev->data;
}

