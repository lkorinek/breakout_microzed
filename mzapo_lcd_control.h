/**
  mzapo_lcd_control.h      - functions to control lcd output on MZAPO

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef MZAPO_LCD_CONTROL
#define MZAPO_LCD_CONTROL

#include <stdint.h>

#include "font_types.h"

/*
 * Initialise display and allocate memory for grid
 */
void init_parlcd(unsigned char *parlcd_mem_base);

/*
 * Reset grid data
 */
void draw_black_screen(unsigned char *parlcd_mem_base);

/*
 * Set all pixel in grid to certain color
 */
void set_display_data_color(unsigned char *parlcd_mem_base, unsigned short color);

/*
 * Store a pixel to a grid
 * color: color of the pixel
 * x and y: position of the pixel
 */
void set_display_data_pixel(unsigned char *parlcd_mem_base, int x, int y, unsigned short color);

/*
 * Draw on display data stored in grid
 */
void draw_display_data(unsigned char *parlcd_mem_base);

/*
 * Draw char on the screen
 * x,y: position
 * ch: char to be printed
 * scale: how much the char should be scaled
 * font: choose from 1 - prop14x16 or 2 - rom8x16
 * color: color of the char
 * background: whether it should print black background
 */
void draw_char(int x, int y, char ch, int scale, int font, unsigned short color, bool background);

/*
 * Draw char on the screen
 * x,y: position
 * str: text to be printed
 * scale: how much the char should be scaled
 * font: choose from 1 - prop14x16 or 2 - rom8x16
 * color: color of the char
 * background: whether it should print black background
 */
void draw_text(char *str, int x, int y, int scale, int font, unsigned short color, bool background);

/*
 * Get width of a char
 * ch: char to be printed
 * font: choose from 1 - prop14x16 or 2 - rom8x16
 * return: width
 */
int char_width(int font, int ch);

/*
 * Draw white line at the top of the barriers in game.
 */
void draw_top_line(unsigned char *parlcd_mem_base);

/*
 * Free allocated memory for display data.
 */
void free_display_data(void);

#endif
