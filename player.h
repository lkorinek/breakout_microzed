/**
  player.h      - functions to create and interact with players

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef PLAYER
#define PLAYER

#include "mzapo_consts.h"

extern game_settings GAME_STATS;

typedef struct {
    int x;
    int y;
    int speed;
    int max_speed;
    int height;
    int width;
    int max_width;
    int lives;
    int score;
    int color;
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
void decrement_player_speed(void);

/*
 * Change player x position
 * x_move: number of pixels to move player
 */
void move_player(unsigned char *parlcd_mem_base, int x_move);

/*
 * Get number of player lifes
 * return: number of lifes
 */
int get_players_lives(void);

/*
 * Decrement player lifes by one
 */
void decrement_players_lives(void);

/*
 * Increment player lifes by one
 */
void increment_players_score(int increment);

/*
 * Get score of the player
 * return: score number
 */
int get_players_score(void);

/*
 * increment player lives by one.
 */
void increment_players_lives(void);

/*
 * increment player width by twenty.
 */
void enlarge_player(void);

/*
 * Get current player max speed.
 * return: max speed
 */
int get_player_max_speed(void);

/*
 * Return all stats of the player
 * return: player struct
 */
player get_player_stats(void);

/*
 * Draw score of the player
 */
void draw_player_score(void);

/*
 * Draw lives of the player
 */
void draw_hearts(void);

/*
 * Change color of the player (in settings).
 */
void change_player_color(int increment);

/*
 * return current color of the player
 * return: player color
 */
unsigned short get_player_color(void);

/*
 * Draw picked difficulity in game.
 */
void draw_difficulity(void);

/*
 * Remove one heart from the screen.
 */
void remove_heart(void);

/*
 * Add one heart to the screen.
 */
void add_heart(void);

/*
 * Change difficulity of the game.
 */
void change_player_stats(void);

/*
 * Reset player width to it's max width.
 */
void reset_player_width(void);

/*
 * Reset player stats.
 */
void reset_player(void);

/*
 * Demo mode, where player is controlled by computer.
 */
void demo_mode(unsigned char *parlcd_mem_base);

#endif