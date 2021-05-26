#include <stdlib.h>
#include <string.h>

#include "font_types.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

#include "mzapo_consts.h"
#include "mzapo_lcd_control.h"

volatile unsigned short *display_data;

void init_parlcd(unsigned char *parlcd_mem_base)
{
    if (parlcd_mem_base == NULL) {
        exit(1);
    }
    parlcd_hx8357_init(parlcd_mem_base);

    display_data = (unsigned short *)malloc(LCD_HEIGHT * LCD_WIDTH * 2);
    set_display_data_color(parlcd_mem_base, 0u);
}

void draw_black_screen(unsigned char *parlcd_mem_base)
{
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (int idx = 0; idx < LCD_WIDTH * LCD_HEIGHT; ++idx) {
        parlcd_write_data(parlcd_mem_base, 0u);
    }
}

void set_display_data_color(unsigned char *parlcd_mem_base, unsigned short color)
{
    for (int idx = 0; idx < LCD_WIDTH * LCD_HEIGHT; ++idx) {
        display_data[idx] = color;
    }
}

void set_display_data_pixel(unsigned char *parlcd_mem_base, int x, int y, unsigned short color)
{
    if (x >= 0 && x < LCD_WIDTH && y >= 0 && y < LCD_HEIGHT) {
        display_data[x + y * LCD_WIDTH] = color;
    }
}

void draw_display_data(unsigned char *parlcd_mem_base)
{
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (int idx = 0; idx < LCD_WIDTH * LCD_HEIGHT; ++idx) {
        parlcd_write_data(parlcd_mem_base, display_data[idx]);
    }
}

void draw_char(int x, int y, char ch, int scale, int font, unsigned short color, bool background)
{
    font_descriptor_t *fdes = font == 1 ? &font_winFreeSystem14x16 : &font_rom8x16;

    int idx = ch - fdes->firstchar;

    for (int i = 0; i < fdes->height * scale; ++i) {
        font_bits_t row = fdes->bits[(idx)*fdes->height + i / scale];
        for (int j = 0; j < fdes->maxwidth * scale; j++) {
            if (background) {
                display_data[j + x + (i + y) * LCD_WIDTH] = 0u;
            }
            if (row & (1 << (15 - j / scale))) {
                display_data[j + x + (i + y) * LCD_WIDTH] = color;
            }
        }
    }
}

void draw_text(char *str, int x, int y, int scale, int font, unsigned short color, bool background)
{

    int length = strlen(str);
    char *curr_point = str;
    for (int i = 0; i < length; ++i) {
        draw_char(x, y, *curr_point, scale, font, color, background);
        x += char_width(font, *curr_point) * scale;
        ++curr_point;
    }
}

int char_width(int font, int ch)
{
    font_descriptor_t *fdes = font == 1 ? &font_winFreeSystem14x16 : &font_rom8x16;

    int width = 0;
    if ((ch >= fdes->firstchar) && (ch - fdes->firstchar < fdes->size)) {
        ch -= fdes->firstchar;
        if (!fdes->width) {
            width = fdes->maxwidth;
        } else {
            width = fdes->width[ch];
        }
    }
    return width;
}

void draw_top_line(unsigned char *parlcd_mem_base)
{
    for (int i = TOP_SPACE - 15; i < TOP_SPACE - 10; ++i) {
        for (int j = 0; j < LCD_WIDTH; j++) {
            set_display_data_pixel(parlcd_mem_base, j, i, 0xffff);
        }
    }
}

void free_display_data(void) { free(display_data); }