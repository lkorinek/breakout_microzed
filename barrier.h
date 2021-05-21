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

typedef struct {
    int x;
    int y;
    int type_upgrade;
    int speed;
    bool falling_upgrade;
} upgrade;

/*
 * Initializes barriers for the game
 */
void init_barriers();

void release_of_upgrade(int upgrade, int x, int y);

void move_upgrade(unsigned char *parlcd_mem_base);

void reset_upgrade();

void initialize_upgrade(int idx);

/*
 * Remove old destroyed barriers and draw them
 */
void update_barriers(unsigned char *parlcd_mem_base);

/*
 * Indicates if the ball should bounce and adds score to the player
 * return: true on bounce, false otherwise
 */
bool bounce_from_barriers(int x, int y, int ball_w , int ball_h,unsigned char *parlcd_mem_base);

#endif