/**
  mzapo_knobs_control.h      - functions to control knobs on MZAPO

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef MZAPO_KNOBS_CONTROL
#define MZAPO_KNOBS_CONTROL

extern game_settings GAME_STATS;

#define SPILED_REG_KBDRD_KNOBS_DIRECT_o 0x020
#define SPILED_REG_KNOBS_8BIT_o 0x024

/*
 * Get initial red knob value.
 */
void init_red_knobs(unsigned char *mem_base);

/*
 * Control movement of the red knob.
 */
void control_red_knob(unsigned char *mem_base, unsigned char *mem_base_lcd);

/*
 * Register knob presses. 
 */
void control_click_knob(unsigned char *mem_base);

#endif