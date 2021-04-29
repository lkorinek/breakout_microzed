/**
  player.h      - functions to create and interact with players

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef PLAYER
#define PLAYER

typedef struct {
    int x;
    int y;
    int height;
    int width;
    int lives;
} player;

void draw_player();

void remove_player();

void move_player_x(int x_move);

void move_player_y(int y_move);

#endif