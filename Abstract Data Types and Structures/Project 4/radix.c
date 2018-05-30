/*
 David Taylor
 Project 4
 
 This file uses radix sorting in order to sort numbers from least to highest.  It uses an array of deques to accomplish this.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "deque.h"

/*
 Sorts inputed numbers from least to greatest.  Does this through radix sorting using an array of deques.  Takes the least significant digit of each number, places it into one of the deques in the array based on its least significant digit, then once all numbers have been placed into a deque, copy them out in the order they appear into the original list.  This process is repeated using the next most significant digit until all digits have been processed. It then prints out the numbers in sorted order, before finally freeing the array of deques.
 */
int main()
{
    int input, maxVal;
    maxVal = 0;
    DEQUE *list = createDeque();
    DEQUE *bins[10];
    int i, j, k;
    for(i = 0; i < 10; i++)
        bins[i] = createDeque();
    printf("Please input positve numbers.  Input q when finished\n");
    
    //Takes user input of positive numbers and stores them in a deque.
    while(scanf("%d", &input) == 1)
    {
        printf("Please input positve numbers.  Input q when finished\n");
        if(input < 0)
        {
            printf("Only positive numbers are accepted\n");
            continue;
        }
        if(input > maxVal)
            maxVal = input;
        
        addFirst(list, input);
    }
    
    int end = numItems(list);
    int divider, index, data;
    divider = 1;
    
    //Begins radix sorting, taking the significant digits and placing the numbers in their respective deques
    for(i = 0; i < ceil(log(maxVal + 1)/log(10)); i++)
    {
        divider *= 10;
        if(i == 0)
            divider = 1;
        //Places the numbers into a deque based on significant digit
        for(j = 0; j < end; j++)
        {
            data = removeFirst(list);
            index = (data / divider) % 10;
            addFirst(bins[index], data);
        }
        //Copies the numbers back out of deques and into the original list
        for(j = 0; j < 10; j++)
        {
            int binEnd = numItems(bins[j]);
            for(k = 0; k < binEnd; k++)
            {
                data = removeFirst(bins[j]);
                addFirst(list, data);
            }
        }
    }
    
    end = numItems(list);
    printf("Sorted List:\n");
    //Prints out the numbers in sorted order
    for(i = 0; i < end; i++)
    {
        data = removeLast(list);
        printf("%d\n", data);
    }
    
    //frees the array of deques
    for(i = 0; i < 10; i++)
        destroyDeque(bins[i]);
    
    destroyDeque(list);
}