/*
 David Taylor
 Project 5
 
 Description: This File uses huffman coding to create a huffman tree in order to compress a file.  This is done by counting the occurences of each character in a given file, creating individual trees for each character that occurs atleast once, then combining these trees into one tree sorted as a min heap.  Then the tree is traveresed to give an encoding value to each character.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include <assert.h>
#include "pack.h"
#include <ctype.h>

#define l(i) (2*i + 1)
#define r(i) (2*i + 2)
#define p(i) ((i-1)/2)

int count = 0;
int counts[257];
struct tree *leaves[257];
struct tree *heap[257];


struct tree *removeMin();
void insert(struct tree *);
void encode(struct tree *);

/*
 Returns the tree with the smallest data
 */
struct tree *removeMin()
{
    int index;
    index = 0;
    struct tree *min;
    struct tree *temp;
    min = heap[0];
    heap[0] = heap[count - 1];
    heap[count - 1] = NULL;
    
    //While I have a left child
    while(heap[l(index)] != NULL)
    {
        //If I have a right child
        if(heap[r(index)] != NULL)
        {
            //If the current tree is bigger than its right or left child
            if(getData(heap[index]) > getData(heap[r(index)]) || getData(heap[index]) > getData(heap[l(index)]))
            {
                //If the left child is smaller than the right child
                if(getData(heap[l(index)]) < getData(heap[r(index)]))
                {
                    //Swap the position of the tree at current index and its left child
                    temp = heap[index];
                    heap[index] = heap[l(index)];
                    heap[l(index)] = temp;
                    index = l(index);
                }
                //If the right child is smaller than or equal to the left child
                else
                {
                    //Swap the position of the tree at current index and its right child
                    temp = heap[index];
                    heap[index] = heap[r(index)];
                    heap[r(index)] = temp;
                    index = r(index);
                }
            }
            //If the current tree is smaller than both its left and right child
            else
                break;
        }
        //If there is no right child
        else
        {
            //If the current tree is bigger than its left child
            if(getData(heap[index]) > getData(heap[l(index)]))
            {
                //Swap the position of the tree at current index and its left child
                temp = heap[index];
                heap[index] = heap[l(index)];
                heap[l(index)] = temp;
                index = l(index);
            }
            //If the current tree is smaller than its left child
            else
                break;
        }
    }


    count--;
    return min;
}

/*
 Takes a tree and inserts it into the heap i
 */
void insert(struct tree *newTree)
{
    assert(newTree != NULL);
    int pos = count;
    //While Im not the root and the new Tree is smaller than its parent
    while(pos > 0 && (getData(newTree) < getData(heap[p(pos)])))
    {
        //Swap the tree at pos with its parent
        heap[pos] = heap[p(pos)];
        pos = p(pos);
    }
    heap[pos] = newTree;
    count++;
    return;
}

/*
 Traverses the huffman tree using post order and prints out the encoding value for the given character
 */
void encode(struct tree *leaf)
{
    assert(leaf != NULL);
    struct tree *currentNode = leaf;
    //If current tree has no parent
    if(getParent(currentNode) == NULL)
        return;
    
    encode(getParent(currentNode));
    //If current tree is the right child of its parent
    if(currentNode == getRight(getParent(currentNode)))
        printf("1");
    //If current tree is the left child of its parent
    else
        printf("0");
    return;
}


int main(int argc, char *argv[])
{
    assert(argc == 3);
    struct tree *combinedTree;
    int data, i;
    FILE *fp;
    
    //Initially set the values in the arrays
    for(i = 0; i < 257; i++)
    {
        counts[i] = 0;
        leaves[i] = NULL;
        heap[i] = NULL;
    }
    
    fp = fopen(argv[1], "r");
    
    /*Counts the occurences of each character and puts them into the count array*/
    char c;
    while((c = fgetc(fp)) != EOF)
    {
        counts[(int)c]++;
    }
    
    /*Creates a leaf for each count > 0, and 1 leaf is created with the data as 0*/
    for(i = 0; i < 256; i++)
    {
        //If the character occurs in the file
        if(counts[i] > 0)
        {
            leaves[i] = createTree(counts[i], NULL, NULL);
            assert(leaves[i] != NULL);
            insert(leaves[i]);
        }
        //If the character doesnt occur in the file
        else
            leaves[i] = NULL;
    }
    leaves[256] = createTree(0, NULL, NULL);
    insert(leaves[256]);
    
    /*Takes all the trees in heap and combines them into one tree, the huffman tree*/
    while(count > 1)
    {
        struct tree *left = removeMin();
        struct tree *right = removeMin();
        data = getData(left) + getData(right);
        combinedTree = createTree(data, left, right);
        insert(combinedTree);
    }
    
    /*Prints out the encoding value for each character*/
    for(i = 0; i < 256; i++)
    {
        char toBePrinted = i;
        int charCount = counts[(int)toBePrinted];
        //If the character appears in the file
        if(leaves[i] != NULL)
        {
            //If the character is printable
            if(isprint(i) != 0)
                printf("'%c': %d ", toBePrinted, charCount);

            //If the character is not printable
            else
                printf("%03o: %d ", toBePrinted, charCount);
            
            encode(leaves[i]);
            printf("\n");
        }
    }
    
    /*prints out the encoding value for the end of file */
    printf("EOF: 0 ");
    encode(leaves[256]);
    printf("\n");
    
    pack(argv[1], argv[2], leaves);
    
    fclose(fp);
    return 0;
}
