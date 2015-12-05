#include <stdio.h>
#include <stdlib.h>
//Stanford Portable Library
#include "gobjects.h"
#include "gwindow.h"


int main(void)
{
    //instantiate window
    GWindow window = newGWindow(WIDTH,HEIGHT);
    int space = 5;
    float brick_width = 34.5;
    float brick_length = 10;
    
    string color[] = {"Red","Orange","Yellow","Green","Blue"};
    //instantiate brick
    for(int j = 0; j < 5; j++)
    {
        for(int i = 0; i < 10 ; i++)
        {
            GRect brick = newGRect(5+i*(brick_width + space),20+j*(brick_length + space), brick_width, brick_length);
            setFilled(brick, true);
            setColor(brick, color[j]);
            add(window, brick);
        }
     
    }
    
    return 0;
}

