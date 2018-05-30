/*
 David Taylor
 Project 5
 
 Description: Contains the implementation of the functions contained within tree.h.  These functions are used to manipulate a tree, primarily returning nodes within a tree, deleting a tree, and adding children to a tree.
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "tree.h"

/*
 Implementation of a tree
 */
struct tree {
    int data;
    struct tree *left, *right, *parent;
};

/*
 Description: Resets a trees parent pointer and its parents leaft or right pointer in order to allow the tree to be added to another tree
 Runtime: O(1)
 */
void cut(struct tree *child)
{
    assert(child != NULL);
    if(child->parent != NULL)
    {
        if(child->parent->left == child)
        {
            child->parent->left = NULL;
            child->parent = NULL;
            return;
        }
        else
        {
            child->parent->right = NULL;
            child->parent = NULL;
            return;
        }
    }
    return;
}

/*
 Desctiption: Creates a new tree, taking its intended data and children as paramaters. Initializes parent pointer to NULL.  Calls cut on the intended children in order to remove them from their previous trees, if they were part of one.
 Runtime: O(1)
 */
struct tree *createTree(int data, struct tree *left, struct tree *right)
{
    struct tree *newTree;
    newTree = malloc(sizeof(struct tree));
    assert(newTree != NULL);
    
    if(left != NULL)
    {
        cut(left);
        left->parent = newTree;
    }
    newTree->left = left;
    
    if(right != NULL)
    {
        cut(right);
        right->parent = newTree;
    }
    newTree->right = right;
    
    newTree->data = data;
    newTree->parent = NULL;
    return newTree;
}


/*
 Description: Destroys the given tree, freeing the memory.  Works recursively using postorder traversal.
 Runtime: O(n)
 */
void destroyTree(struct tree *root)
{
    if(root == NULL)
        return;
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
    return;
}

/*
 Desctiption: Returns the data of given tree
 Runetime: O(1)
 */
int getData(struct tree *root)
{
    assert(root != NULL);
    return root->data;
}

/*
 Desctiption: Returns a pointer to the left child of a given tree
 Runetime: O(1)
 */
struct tree *getLeft(struct tree *root)
{
    assert(root != NULL);
    return root->left;
}

/*
 Desctiption: Returns a pointer to the right child of a given tree
 Runetime: O(1)
 */
struct tree *getRight(struct tree *root)
{
    assert(root != NULL);
    return root->right;
}

/*
 Desctiption: Returns a pointer to the parent of a given tree
 Runetime: O(1)
 */
struct tree *getParent(struct tree *root)
{
    assert(root != NULL);
    return root->parent;
}

/*
 Desctiption: Takes pointers to two trees, one being a root and another being the intended left child.  Removes the intended left child from any previous trees using cut, then sets the roots left pointer to the intended left child, and the new left child's parent pointer to the root.
 Runetime: O(1)
 */
void setLeft(struct tree *root, struct tree *left)
{
    assert(root != NULL && left != NULL);
    cut(left);
    
    if(root->left != NULL)
        cut(root->left);
    
    root->left = left;
    left->parent = root;
    return;
}

/*
 Desctiption: Takes pointers to two trees, one being a root and another being the intended right child.  Removes the intended right child from any previous trees using cut, then sets the root's right pointer to the intended right child, and the new right child's parent pointer to the root.
 Runetime: O(1)
 */
void setRight(struct tree *root, struct tree *right)
{
    assert(root != NULL && right != NULL);
    cut(right);
    
    if(root->right != NULL)
        cut(root->right);
    
    root->right = right;
    right->parent = root;
    return;
}




