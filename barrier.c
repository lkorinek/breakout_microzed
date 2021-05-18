#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "mzapo_lcd_control.h"

#include "mzapo_consts.h"

#include "barrier.h"
#include "player.h"

#define NUMBER_OF_BARRIERS 20

barrier our_barriers[NUMBER_OF_BARRIERS];

unsigned short colors[] = {0xf0f,0xfff,0xf0f,0xfff};
void init_barriers()
{
    int x = 0, y = 0, shift = 15;
    for (int i = 0; i < NUMBER_OF_BARRIERS; ++i) {
        our_barriers[i].x = x;
        our_barriers[i].y = y;
        our_barriers[i].height = 25;
        our_barriers[i].width = 80;
        our_barriers[i].destroyed = false;
        x += our_barriers[i].width + shift;
        if (x >= (LCD_WIDTH - shift)) {
            x = 0;
            y += 25 + shift;
        }
    }
}

void draw_barriers(unsigned char *parlcd_mem_base)
{
    int color_number = 0;
    for (int b = 0; b < NUMBER_OF_BARRIERS; ++b) {
        if (b != 0 && b %5 == 0)
        {
            ++color_number;
        }
        for (int i = 0; i < our_barriers[b].width; ++i) {
            for (int j = 0; j < our_barriers[b].height; ++j) {
                set_display_data_pixel(parlcd_mem_base, our_barriers[b].x + i, our_barriers[b].y + j, colors[color_number]);
            }
        }      
    }
}

void update_barriers(unsigned char *parlcd_mem_base) {
    int color_number = 0;
    for (int b = 0; b < NUMBER_OF_BARRIERS; ++b) {
        for (int i = 0; i < our_barriers[b].width; ++i) {
            for (int j = 0; j < our_barriers[b].height; ++j) {
                if (!our_barriers[b].destroyed)
                {
                    set_display_data_pixel(parlcd_mem_base, our_barriers[b].x + i, our_barriers[b].y + j, colors[color_number]);
                }
                else {
                    set_display_data_pixel(parlcd_mem_base, our_barriers[b].x + i, our_barriers[b].y + j, 0u);
                }
            }
        }
        if (b != 0 && b %5 == 0)
        {
            ++color_number;
        }   
    }
}


bool bounce_from_barriers(int x, int y, int ball_w , int ball_h,unsigned char *parlcd_mem_base) {
    bool ret = false;
    for (int i = NUMBER_OF_BARRIERS; i >=0 ; --i)
    {
        if ((x+ball_w) > (our_barriers[i].x) && (our_barriers[i].x + our_barriers[i].width) > x && (y - ball_h) < (our_barriers[i].y + our_barriers[i].height) && !our_barriers[i].destroyed)
        {
            ret = true;
            our_barriers[i].destroyed = true;
            increment_players_score();
            update_barriers(parlcd_mem_base);
            break;
        }
    }
    return ret;
}
