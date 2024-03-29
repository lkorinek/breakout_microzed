#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mzapo_consts.h"
#include "mzapo_lcd_control.h"
#include "mzapo_led_control.h"

#include "ball.h"
#include "barrier.h"
#include "player.h"

const int speed = 7;
int last_x = 0;
int last_y = 0;

static ball ball_1 = {.x = LCD_WIDTH / 2 - 50, .y = LCD_HEIGHT - 60, .height = 9, .width = 9, .increment_x = speed, .increment_y = -speed};

void reset_ball(void)
{
    ball_1.x = LCD_WIDTH / 2;
    ball_1.y = LCD_HEIGHT - 60;
    ball_1.increment_x = speed;
    ball_1.increment_y = -speed;
    last_x = 0;
    last_y = 0;
}

void move_ball(unsigned char *parlcd_mem_base)
{
    delete_ball(parlcd_mem_base);

    if (ball_1.x >= LCD_WIDTH - ball_1.width || ball_1.x <= ball_1.width) {
        ball_1.increment_x = -ball_1.increment_x;
    }
    if (ball_1.y <= ball_1.height + TOP_SPACE - 15 || ball_1.y >= LCD_HEIGHT - ball_1.height) {
        ball_1.increment_y = -ball_1.increment_y;
        if (ball_1.y >= LCD_HEIGHT - ball_1.height) {
            decrement_players_lives();
            reset_ball();
        }
    }

    bounce_ball(parlcd_mem_base);

    ball_1.x += ball_1.increment_x;
    ball_1.y += ball_1.increment_y;

    demo_mode(parlcd_mem_base);
    draw_ball(parlcd_mem_base);
}

void bounce_ball(unsigned char *parlcd_mem_base)
{
    player p_1 = get_player_stats();

    if ((ball_1.x + ball_1.width) > p_1.x && (p_1.x + p_1.width) > ball_1.x && (ball_1.y + ball_1.height) > p_1.y &&
        (p_1.y + p_1.height) > ball_1.y) {
        ball_1.increment_y = -ball_1.increment_y;
        if ((p_1.x + p_1.width / 4 > ball_1.x && ball_1.increment_x > 0) ||
            (p_1.x + p_1.width - p_1.width / 4 < ball_1.x && ball_1.increment_x < 0)) {
            ball_1.increment_x = -ball_1.increment_x;
        }
    }
    if (bounce_from_barriers(ball_1.x, ball_1.y, ball_1.width, ball_1.height, parlcd_mem_base)) {
        ball_1.increment_y = -ball_1.increment_y;
    }
}

void change_ball_y_speed(void) { ball_1.increment_y = -ball_1.increment_y; }

int get_ball_x_position(void) { return ball_1.x; }

void draw_ball(unsigned char *parlcd_mem_base)
{
    for (int i = 0; i < ball_1.width; ++i) {
        for (int j = 0; j < ball_1.height; ++j) {
            set_display_data_pixel(parlcd_mem_base, ball_1.x + i, ball_1.y + j, 0xffff);
        }
    }
}

void delete_ball(unsigned char *parlcd_mem_base)
{
    for (int i = 0; i < ball_1.width; ++i) {
        for (int j = 0; j < ball_1.height; ++j) {
            set_display_data_pixel(parlcd_mem_base, ball_1.x + i, ball_1.y + j, 0u);
        }
    }
}

void freeze_ball(bool freeze)
{
    if (freeze) {
        last_x = ball_1.increment_x;
        last_y = ball_1.increment_y;
        ball_1.increment_x = 0;
        ball_1.increment_y = 0;
    } else {
        ball_1.increment_x = last_x;
        ball_1.increment_y = last_y;
    }
}

void change_ball_speed(int speed) { ball_1.increment_y = -speed; }
