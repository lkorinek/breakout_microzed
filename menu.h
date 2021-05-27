/**
  menu.h      - create and control menu

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef MENU
#define MENU

#include <stdbool.h>

#include "mzapo_consts.h"
#include "threads.h"

extern game_settings GAME_STATS;

typedef struct {
    int menu_selected;
    int menu_selected_max;
    bool run;
    bool credits;
    bool settings;
    int settings_selected;
    int settings_selected_max;
    bool change_color;
} menu_stats;

/*
 * Function to create a menu in a while loop.
 */
void draw_menu(unsigned char *parlcd_mem_base, shared_data *data);

/*
 * Store a box around the menu with title to a display data.
 */
void draw_menu_box(unsigned char *parlcd_mem_base);

/*
 * Store menu options to display data.
 */
void draw_menu_options(void);

/*
 * Change which menu option is selected.
 * increment: how much to move up or down (usually -1/1).
 */
void change_menu_state(int increment);

/*
 * Store a game over screen to display data.
 */
void game_over_screen(unsigned char *parlcd_mem_base);

/*
 * Pick a selected menu option (in main menu or settings).
 */
void forward_selected_option_menu(void);

/*
 * Reset application to the main menu.
 */
void reset_menu(void);

/*
 * Draw credits in menu.
 */
void draw_menu_credits(unsigned char *parlcd_mem_base);

/*
 * Draw settings options in menu.
 */
void draw_menu_settings(unsigned char *parlcd_mem_base);

/*
 * Get the x position of text in menu to be placed at.
 * text: text to be drawn
 * return: x position of the text
 */
int get_menu_position(char *text);

/*
 * Draw a text in menu on certain position
 * y: y position on the screen
 * text: text to be drawn
 * selected: whether the option is selected or not 
 */
void draw_menu_text(int y, char *text, bool selected);
#endif