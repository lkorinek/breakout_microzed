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
    int speed;
    int height;
    int width;
    int lives;
    int score;
} player;

void draw_player(unsigned char *parlcd_mem_base);

void remove_player(unsigned char *parlcd_mem_base);

void set_player_speed(int speed);

void decrement_player_speed();

void move_player(unsigned char *parlcd_mem_base, int x_move);

int get_players_lives();

void decrement_players_lives();

void increment_players_score();

int get_players_score();

player get_player_stats();

#endif