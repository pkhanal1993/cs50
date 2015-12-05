//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

//paddle length and height
float paddle_length = 50;
float paddle_height = 10;


// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // set the velocities in x and y directions
    double dx = drand48()*0.025;
    double dy = 0.05;

    waitForClick();
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        
        // moving the paddle
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows top cursor
                double x = getX(event) - getWidth(paddle) / 2;
                if(x <= 0)
                    x = 0;
                else if(x >= WIDTH-paddle_length)
                    x = WIDTH - paddle_length;
                double y = getY(paddle);
                setLocation(paddle, x, y);
            }
        }
        
        // move the ball
        move(ball, dx, dy);
        
        // bounce off the horizontal walls
        if (getX(ball) <= 0 || (getX(ball) + getWidth(ball) >= getWidth(window)))
        {
            dx = -dx;
        }
        
        //bounce off the vertical walls
        if (getY(ball) <= 0)
        {
            dy = -dy;
        }
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            removeGWindow(window, ball);
            ball = initBall(window);
            removeGWindow(window, paddle);
            paddle = initPaddle(window);
            lives--;
            waitForClick();
        }    
        
        // detect collisions
        if (detectCollision(window, ball) != NULL)
        {
            GObject object = detectCollision(window, ball);
          
            if ((strcmp(getType(object), "GRect")) == 0)
            {
                dy = -dy;
                if (object != paddle)
                {
                    removeGWindow(window, object);
                    points++;
                    bricks--;
                    updateScoreboard(window, label, points);
                }   
            }
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // declare variables used for creating the grid of bricks
    int space = 5;
    float brick_width = (WIDTH - space * (COLS + 1))/10.0 ;
    float brick_length = 10;
    string color[] = {"Red","Orange","Yellow","Green","Blue"};
    
    //instantiate bricks
    for(int j = 0; j < ROWS; j++)
    {
        for(int i = 0; i < COLS ; i++)
        {
            GRect brick = newGRect(space+i*(brick_width + space), 20+j*(brick_length + space), brick_width, brick_length);
            setFilled(brick, true);
            setColor(brick, color[j]);
            add(window, brick);
        }
     
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // instantiate ball
    float x = (WIDTH/2 - RADIUS);
    float y = (HEIGHT/2 - RADIUS);
    GOval ball = newGOval(x, y, RADIUS*2, RADIUS*2);
    setFilled(ball, true);
    setColor(ball, "Black");
    add(window, ball);
    return ball;
    
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // declare variables
    
    float x = WIDTH/2 - paddle_length/2;
    float y = HEIGHT/1.5 - paddle_height/2;
    
    //instantiate paddle
    GRect paddle = newGRect(x, y, paddle_length, paddle_height);
    setFilled(paddle, true);
    setColor(paddle, "Black");
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // instantiate scoreboard
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    char s[3];
    sprintf(s, "%i", 0);
    setLabel(label, s);
    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    
    add(window, label); 
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[3];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
