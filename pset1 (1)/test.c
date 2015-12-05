#include<stdio.h>
#include<math.h>
#include<cs50.h>

int main(void)
{
    float x;
    do
    {
        x = GetFloat();
        int y = round(x*100);
        printf("%d\n",y);    
    
    } while (x != -1);
}
