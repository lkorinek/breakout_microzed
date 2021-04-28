/**
  mzapo_led_functions.h      -functions for operations with led and RGB on MZAPO

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef MZAPO_LED_FUNCTIONS
#define MZAPO_LED_FUNCTIONS

/*
 * turn on RGB diod
 * color: which color will turn on
 * RGB: which RGB should turn on (there are to -> 1 or 2)
 */
void turn_on_RGB(volatile uint32_t color, int RGB);

/*
 * turn off RGB diod
 * RGB: which RGB should turn off
 */
void turn_off_RGB(int RGB);

#endif
