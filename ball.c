#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "mzapo_consts.h"
#include "ball.h"
#include "mzapo_lcd_control.h"
#include "mzapo_led_control.h"
#include "player.h"


static ball ball_1 = {.x = LCD_WIDTH/2, .y = LCD_HEIGHT-15, .height = 10, .width = 10, .increment_x = 10, .increment_y = -10, .lifes = 4};

int move_ball() {
	draw_ball();
	delete_ball();
	
	if (ball_1.x >= LCD_WIDTH-ball_1.width || ball_1.x <= ball_1.width) {
			ball_1.increment_x = -ball_1.increment_x;
		}
		if (ball_1.y <= ball_1.height || ball_1.y >= LCD_HEIGHT-ball_1.height) {
			ball_1.increment_y = -ball_1.increment_y;
			if (ball_1.y >= LCD_HEIGHT-ball_1.height) {
				ball_1.lifes--;
				control_led_line(ball_1.lifes);
				printf("LIFE DOWN\n");
				ball_1.x = LCD_WIDTH/2;
				ball_1.y = LCD_HEIGHT-15;
				ball_1.increment_x = 10;
				ball_1.increment_y = -10;
			}
		}
	ball_1.x += ball_1.increment_x;
	ball_1.y += ball_1.increment_y;
	
	return ball_1.lifes;
}

void draw_ball() {
	for (int i = 0; i < ball_1.width; ++i) {
		    for (int j = 0; j < ball_1.height; ++j) {
		        set_display_data_pixel(ball_1.x + i, ball_1.y + j, 0xfff);
		    }
		}
	draw_display_data();
}

void delete_ball() {
	for (int i = 0; i < ball_1.width; ++i) {
		    for (int j = 0; j < ball_1.height; ++j) {
		        set_display_data_pixel(ball_1.x + i, ball_1.y + j, 0u);
		    }
		}
	draw_display_data();
}

