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


void init_barriers();

void draw_barriers(unsigned char *parlcd_mem_base);

void update_barriers(unsigned char *parlcd_mem_base);

bool bounce_from_barriers(int x, int y, int ball_w , int ball_h,unsigned char *parlcd_mem_base);

#endif