/**
  terminal.h      - functions to change terminal settings and interact with terminal

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef TERMINAL
#define TERMINAL

/*
 * Set terminal to raw mode.
 * bool set: true to set raw mode and false to reset terminal setting.
 */
void set_terminal_raw(bool set);

/*
 * Get input from terminal.
 * return: pressed key
 */
char get_terminal_input(void);

void control_game(char c);
void control_menu(char c);

#endif