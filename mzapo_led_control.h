/**
  mzapo_led_control.h      -functions for operations with led and RGB on MZAPO

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

/*
 * turn on/off number of lifes on the led line
 * lifes: number of lifes you have (1-4)
 * return : 0 on succes -1 on incorrect
 */
int led_line(int lifes);

#endif
