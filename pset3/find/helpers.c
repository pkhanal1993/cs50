/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include<stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if(value<0)
        return false;
    
    int min = 0;
    int max = n-1;
    
    do
    {
        int midpoint = (min+max)/2;
        if(values[midpoint] < value)
            min = midpoint+1;
        else if(values[midpoint] > value)
            max = midpoint-1;
        else if(values[midpoint] == value)
            return true;
    
    }while(min <= max);     //end do-while
    return false;
}

/**
 * Sorts array of n values
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for(int j = 0, k = 1; j < n-1 ; j++)               
    {
        for(int i = 0; i < n-k; i++)
        {
            if (values[i] > values[i+1])
            {
                int temp = values[i];
                values[i] = values[i+1];
                values[i+1] = temp;
            }   
        }//end inside loop
        
        // k is incremented so that we won't have to check for the rightmost elements which are already sorted
        k++;
        
    }//end outside loop
    for(int i = 0; i <n ; i++)
        printf("%d\t",values[i]);
    return;
}
