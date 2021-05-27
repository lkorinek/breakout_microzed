/**
  barrier.h      - functions to create and destory barriers

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef BARRIER
#define BARRIER

// informations about our barriers
typedef struct {
    int x;
    int y;
    int height;
    int width;
    bool destroyed;
} barrier;

// informations about our upgrades
typedef struct {
    int x;
    int y;
    int type_upgrade;
    int speed;
    bool falling_upgrade; // if some upgrade is already falling
} upgrade;

/*
 * Initializes barriers for the game
 */
void init_barriers(void);

/*
 * selects the color and char for the update and lets it fall
 * upgrade falls only if another update is not falling
 */
void move_upgrade(unsigned char *parlcd_mem_base);

/*
 * resets the informations about upgrade
 */
void reset_upgrade(void);

/*
 * Initializes informations about upgrades
 */
void initialize_upgrade(int idx);

/*
 * Remove old destroyed barriers
 */
void update_barriers(unsigned char *parlcd_mem_base);

/*
 * Indicates if the ball should bounce and add score to the player
 * input: x,y = position of the ball, ball_w,ball_h = size of ball
 * return: true on bounce, false otherwise
 */
bool bounce_from_barriers(int x, int y, int ball_w, int ball_h, unsigned char *parlcd_mem_base);

#endif