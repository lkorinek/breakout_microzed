/**
  mzapo_lcd_control.h      - functions to control lcd output on MZAPO

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef MZAPO_LCD_CONTROL
#define MZAPO_LCD_CONTROL

#include <stdint.h>

void init_parlcd(unsigned char *parlcd_mem_base);

void draw_black_screen(unsigned char *parlcd_mem_base);

void set_display_data_color(unsigned char *parlcd_mem_base, unsigned short color);

void set_display_data_pixel(unsigned char *parlcd_mem_base, int x, int y, unsigned short color);

void draw_display_data(unsigned char *parlcd_mem_base);

#endif
