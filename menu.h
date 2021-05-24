/**
  mzapo_consts.h      -constants we are using

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

void draw_menu(unsigned char *parlcd_mem_base, shared_data *data);
void draw_menu_box(unsigned char *parlcd_mem_base);
void draw_menu_options(void);
void change_menu_state(int increment);
void game_over_screen(unsigned char *parlcd_mem_base);
void forward_selected_option_menu(void);
void reset_menu(void);
void reset_change_color(void);
void draw_menu_credits(unsigned char *parlcd_mem_base);
void draw_menu_settings(unsigned char *parlcd_mem_base);
int get_menu_position(char *text);
void draw_menu_text(int y, char *text, int selected);
#endif