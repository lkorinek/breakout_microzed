/**
  ball.h      - functions to create and move with ball

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef BALL
#define BALL

/*
 * struct for our ball
 * x,y coordinates
 * height: height of the ball
 * width: width of the ball
 * increment_x, increment_y = how fast the ball moves
 */
typedef struct {
    int x;
    int y;
    int height;
    int width;
    int increment_x;
    int increment_y;
} ball;

/*
 * this function moves ball around
 */
void move_ball(unsigned char *parlcd_mem_base);

/*
 * function for drawing the ball
 */
void draw_ball(unsigned char *parlcd_mem_base);

/*
 * function to bounce ball of the platforms (players)
 */
void bounce_ball(unsigned char *parlcd_mem_base);

/*
 * function for deleting the ball
 */
void delete_ball(unsigned char *parlcd_mem_base);

/*
 * resets ball to start position
 */
void reset_ball(void);

/*
 * freezes/unfreezes ball
 * input: freeze: if the ball should move or not
 */
void freeze_ball(bool freeze);

/*
 * changes the speed in y-axe
 * input: speed: the increment ball should have in y-axe
 */
void change_ball_speed(int speed);

/*
 * changes the balls direction in y-axe 
 */
void change_ball_y_speed(void);

/*
 * returns the x position of the ball
 */
int get_ball_x_position(void);

#endif