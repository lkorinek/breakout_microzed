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
 * Get input from terminal control game and menu.
 * return: pressed key
 */
char get_terminal_input(void);

/*
 * Control game with keyboard.
 * c: pressed char
 */
void control_game(char c);

/*
 * Conrol menu with keyboard.
 * c: pressed char
 */
void control_menu(char c);

#endif