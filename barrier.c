#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "mzapo_lcd_control.h"

#include "mzapo_consts.h"

#include "barrier.h"
#include "player.h"

#define NUMBER_OF_BARRIERS_IN_ROW 5
#define NUMBER_OF_ROWS 6

barrier our_barriers[NUMBER_OF_BARRIERS_IN_ROW * NUMBER_OF_ROWS];


unsigned short colors[] = {0xf800,0xf7e0,0xf0f,0xffD5, 0xffD5, 0xffD5};
const int space_for_text = 60;

void init_barriers()
{
    int x = 0, y = space_for_text, shift = 5;
    for (int i = 0; i < NUMBER_OF_BARRIERS_IN_ROW * NUMBER_OF_ROWS; ++i) {
        our_barriers[i].x = x;
        our_barriers[i].y = y;
        our_barriers[i].height = 10;
        our_barriers[i].width = LCD_WIDTH/(NUMBER_OF_BARRIERS_IN_ROW)-shift;
        our_barriers[i].destroyed = false;
        x += our_barriers[i].width + shift;
        if (x >= (LCD_WIDTH - shift)) {
            x = 0;
            y += our_barriers[i].height + shift;
        }
    }
}

void update_barriers(unsigned char *parlcd_mem_base) {
    int color_number = 0;
    for (int b = 0; b < NUMBER_OF_BARRIERS_IN_ROW * NUMBER_OF_ROWS; ++b) {
        if (b != 0 && b % NUMBER_OF_BARRIERS_IN_ROW == 0)
        {
            ++color_number;
        }  
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
    }
}


bool bounce_from_barriers(int x, int y, int ball_w , int ball_h,unsigned char *parlcd_mem_base) {
    bool ret = false;
    for (int i = NUMBER_OF_BARRIERS_IN_ROW * NUMBER_OF_ROWS; i >= 0; --i)
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
