/**
  mzapo_lcd_control.h      - functions to control lcd output on MZAPO

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef MZAPO_LCD_CONTROL
#define MZAPO_LCD_CONTROL

#define PARLCD_MEM_BASE map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0)


void init_parlcd(void);

void draw_black_screen(void);

void set_display_data_color(unsigned short color);

void set_display_data_pixel(int x, int y, unsigned short color);

void draw_display_data(void);

#endif
