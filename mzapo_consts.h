/**
  mzapo_consts.h      -constants we are using

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef MZAPO_CONSTS
#define MZAPO_CONSTS

#include <stdbool.h>

// mainly for mzapo_led_functions
#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff

//constants lcd
#define LCD_WIDTH 480
#define LCD_HEIGHT 320

// Space for score on top of the screen
#define TOP_SPACE 60

typedef struct {
  bool menu;
  bool exit;
  int difficulity;
  int num_players;
  int controls;
} game_settings;

#endif