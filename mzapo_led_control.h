/**
  mzapo_led_control.h      -functions for operations with led and RGB on MZAPO

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef MZAPO_LED_CONTROL
#define MZAPO_LED_CONTROL

#define SPILED_MEM_BASE map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0)
/*
 * turns on RGB diod
 * color: which color will turn on
 * RGB: which RGB should turn on (there are to -> 1 or 2)
 */
void turn_on_RGB(volatile uint32_t color, int RGB);

/*
 * turns off RGB diod
 * RGB: which RGB should turn off
 */
void turn_off_RGB(int RGB);

/*
 * turns on/off number of lifes on the led line
 * lifes: number of lifes you have (1-4)
 * return : true on succes false on error (mainly caused by incorrect input)
 */
bool control_led_line(int lifes);

#endif
