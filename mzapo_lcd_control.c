#include <stdlib.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

#include "mzapo_lcd_control.h"

static unsigned short *display_data;

void init_parlcd(void)
{
    if (PARLCD_MEM_BASE == NULL) {
        exit(1);
    }
    parlcd_hx8357_init(PARLCD_MEM_BASE);

    display_data = (unsigned short *)malloc(LCD_HEIGHT * LCD_WIDTH * 2);
    set_display_data_color(0u);
}

void draw_black_screen(void)
{
    unsigned char *parlcd_mem_base = PARLCD_MEM_BASE;
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (int idx = 0; idx < LCD_WIDTH * LCD_HEIGHT; ++idx) {
        parlcd_write_data(parlcd_mem_base, 0u);
    }
}

void set_display_data_color(unsigned short color)
{
    for (int idx = 0; idx < LCD_WIDTH * LCD_HEIGHT; ++idx) {
        display_data[idx] = color;
    }
}

void set_display_data_pixel(int x, int y, unsigned short color)
{
    if (x >= 0 && x < LCD_WIDTH && y >= 0 && y < LCD_HEIGHT) {
        display_data[x + y * LCD_WIDTH] = color;
    }
}

void draw_display_data(void)
{
    unsigned char *parlcd_mem_base = PARLCD_MEM_BASE;
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (int idx = 0; idx < LCD_WIDTH * LCD_HEIGHT; ++idx) {
        parlcd_write_data(parlcd_mem_base, display_data[idx]);
    }
}