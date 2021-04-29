/**
  terminal.h      - functions to change terminal settings and interact with terminal

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef TERMINAL
#define TERMINAL

void set_terminal_raw(bool set);

char get_terminal_input(void);

#endif