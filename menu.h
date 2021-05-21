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

void draw_menu(unsigned char *parlcd_mem_base, shared_data *data);
void draw_menu_box(unsigned char *parlcd_mem_base);
void draw_menu_options(void);
void change_menu_state(int increment);
void game_over_screen(unsigned char *parlcd_mem_base);
void forward_selected_option_menu(void);

#endif