/**
  player.h      - functions to create and interact with players

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef PLAYER
#define PLAYER

/*
 * struct for our ball
 * x,y coordinates
 * height: height of the ball
 * width: width of the ball
 * increment_x, increment_y = how fast the ball is moving
 * lifes: lifes of our player
 */
typedef struct {
    int x;
    int y;
    int height;
    int width;
    int increment_x;
    int increment_y;
    int lifes;
} ball;

/*
 * this function moves ball around
 * input: none
 * return: number of lifes of the ball
 */
int move_ball();

/*
 * function for drawing the ball
 * input: none
 * output: none
 *
 */
void draw_ball();

/*
 * function for deleting the ball
 * input: none
 * output: none
 */
void delete_ball();

#endif
