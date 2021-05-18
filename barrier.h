/**
  player.h      - functions to create and interact with players

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef BARRIER
#define BARRIER

typedef struct {
    int x;
    int y;
    int height;
    int width;
    bool destroyed;
} barrier;


/*
 * Initializes barriers for the game
 */
void init_barriers();


/*
 * Draws barriers to the display
 */
void draw_barriers(unsigned char *parlcd_mem_base);

/*
 * Remove old destroyed barriers 
 */
void update_barriers(unsigned char *parlcd_mem_base);

/*
 * Indicates if the ball should bounce and adds score to the player
 * return: true on bounce, false otherwise
 */
bool bounce_from_barriers(int x, int y, int ball_w , int ball_h,unsigned char *parlcd_mem_base);

#endif