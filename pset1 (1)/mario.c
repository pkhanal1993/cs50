/**
* This program draws the mario's wall
*
*/

#include<cs50.h>
#include<stdio.h>

int main(void)
{
    int height;
    // makes sure the height is input correctly
    do
    {
        printf("Height:");
        height = GetInt();
    } while (height < 0 || height > 23);
    
    // draws the wall
    for(int i = 1; i <= height; i++)
    {
        // prints the spaces
        for(int j = 1; j <= height-i; j++)
        {
            printf(" ");
        }
        
        // prints the #s
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
        
    }
}
