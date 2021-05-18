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

/*
 * Remove old and store new position of the player to grid
 */
void draw_player(unsigned char *parlcd_mem_base);

/*
 * Remove player from a grid
 */
void remove_player(unsigned char *parlcd_mem_base);

/*
 * Set player speed
 * speed: number of pixels to move in one cycle
 */
void set_player_speed(int speed);

/*
 * Decrement player speed by one
 */
void decrement_player_speed();

/*
 * Change player x position
 * x_move: number of pixels to move player
 */
void move_player(unsigned char *parlcd_mem_base, int x_move);

/*
 * Get number of player lifes
 * return: number of lifes
 */
int get_players_lives();

/*
 * Decrement player lifes by one
 */
void decrement_players_lives();

/*
 * Increment player lifes by one
 */
void increment_players_score();

/*
 * Get score of the player
 * return: score number
 */
int get_players_score();

/*
 * Return all stats of the player
 * return: player struct
 */
player get_player_stats();

#endif