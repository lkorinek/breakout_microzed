#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ball.h"
#include "mzapo_consts.h"
#include "mzapo_lcd_control.h"
#include "mzapo_led_control.h"
#include "player.h"

static ball ball_1 = {
    .x = LCD_WIDTH / 2, .y = LCD_HEIGHT - 15, .height = 10, .width = 10, .increment_x = 10, .increment_y = -10};

void reset_ball()
{
    ball_1.x = LCD_WIDTH / 2;
    ball_1.y = LCD_HEIGHT - 15;
    ball_1.increment_x = 10;
    ball_1.increment_y = -10;
}

void move_ball()
{
    draw_ball();
    delete_ball();

    if (ball_1.x >= LCD_WIDTH - ball_1.width || ball_1.x <= ball_1.width) {
        ball_1.increment_x = -ball_1.increment_x;
    }
    if (ball_1.y <= ball_1.height || ball_1.y >= LCD_HEIGHT - ball_1.height) {
        ball_1.increment_y = -ball_1.increment_y;
        if (ball_1.y >= LCD_HEIGHT - ball_1.height) {
            decrement_players_lives();
            control_led_line(get_players_lives());
            reset_ball();
        }
    }
    ball_1.x += ball_1.increment_x;
    ball_1.y += ball_1.increment_y;
}

void draw_ball()
{
    for (int i = 0; i < ball_1.width; ++i) {
        for (int j = 0; j < ball_1.height; ++j) {
            set_display_data_pixel(ball_1.x + i, ball_1.y + j, 0xfff);
        }
    }
    draw_display_data();
}

void delete_ball()
{
    for (int i = 0; i < ball_1.width; ++i) {
        for (int j = 0; j < ball_1.height; ++j) {
            set_display_data_pixel(ball_1.x + i, ball_1.y + j, 0u);
        }
    }
    draw_display_data();
}
