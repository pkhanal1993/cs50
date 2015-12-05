/*
* This program gives the least number of coins required to give the given change
*
*/

#include<cs50.h>
#include<stdio.h>
#include<math.h>

int main(void)
{
    float change;
    // ask the user for input 
    printf("O hai! How much change is owed?\n");
    change = GetFloat();
    
    //check for the correct input
    while (change < 0)
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    }
    
    // converts the change amount to cents
    int cents = round(change*100);
    
    // calculates the number of coins
    int num_coins = cents/25 + (cents%25)/10 + ((cents%25)%10)/5 + (((cents%25)%10)%5)/1;
    printf("%d\n",num_coins); 
}
