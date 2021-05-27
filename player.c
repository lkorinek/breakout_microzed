#include <stdbool.h>
#include <stdio.h>

#include "mzapo_lcd_control.h"

#include "ball.h"
#include "mzapo_consts.h"
#include "mzapo_led_control.h"
#include "player.h"

const int max_colors = 6;
const unsigned short player_colors[] = {0xf80b, 0xfD00, 0xffe0, 0x7e0, 0x3ff, 0xD017};
static player player_1 = {.x = LCD_WIDTH / 2,
                          .y = LCD_HEIGHT - 30,
                          .height = 11,
                          .width = 100,
                          .max_width = 100,
                          .speed = 0,
                          .max_speed = 8,
                          .lives = 4,
                          .score = 0,
                          .color = 0};

void draw_player(unsigned char *parlcd_mem_base)
{
    remove_player(parlcd_mem_base);
    if (player_1.speed != 0 && !GAME_STATS.freeze) {
        move_player(parlcd_mem_base, player_1.speed);
    }

    for (int i = 0; i < player_1.width; ++i) {
        for (int j = 0; j < player_1.height; ++j) {
            set_display_data_pixel(parlcd_mem_base, player_1.x + i, player_1.y + j, player_colors[player_1.color]);
        }
    }
}

void remove_player(unsigned char *parlcd_mem_base)
{
    for (int i = 0; i < player_1.width; ++i) {
        for (int j = 0; j < player_1.height; ++j) {
            set_display_data_pixel(parlcd_mem_base, player_1.x + i, player_1.y + j, 0u);
        }
    }
}

void set_player_speed(int speed) { player_1.speed = speed; }

int get_player_max_speed(void) { return player_1.max_speed; }

void decrement_player_speed(void)
{
    if (player_1.speed > 0) {
        player_1.speed -= 1;
    } else if (player_1.speed < 0) {
        player_1.speed += 1;
    }
}

void change_player_color(int increment)
{
    player_1.color += increment;
    if (player_1.color > max_colors - 1) {
        player_1.color = 0;
    } else if (player_1.color < 0) {
        player_1.color = max_colors - 1;
    }
}

unsigned short get_player_color(void) { return player_colors[player_1.color]; }

void move_player(unsigned char *parlcd_mem_base, int x_move)
{

    bool move = true;
    if (player_1.x + player_1.width > LCD_WIDTH && x_move > 0) {
        move = false;
    } else if (player_1.x < 0 && x_move < 0) {
        move = false;
    }

    if (move) {
        remove_player(parlcd_mem_base);
        int new_x_pos = player_1.x + x_move;
        for (int i = 0; i < player_1.width; ++i) {
            for (int j = 0; j < player_1.height; ++j) {
                set_display_data_pixel(parlcd_mem_base, new_x_pos + i, player_1.y + j, player_colors[player_1.color]);
            }
        }

        player_1.x += x_move;
    }
}

void demo_mode(unsigned char *parlcd_mem_base)
{
    remove_player(parlcd_mem_base);
    if (GAME_STATS.demo_mode) {
        int new_x_pos = get_ball_x_position() - player_1.width / 2;
        if (new_x_pos + player_1.width < LCD_WIDTH && new_x_pos > 0) {
            player_1.x = new_x_pos;
        }
    }
    for (int i = 0; i < player_1.width; ++i) {
        for (int j = 0; j < player_1.height; ++j) {
            set_display_data_pixel(parlcd_mem_base, player_1.x + i, player_1.y + j, player_colors[player_1.color]);
        }
    }
}
int get_players_lives(void) { return player_1.lives; }

void increment_players_lives(void)
{
    if (player_1.lives < 4) {
        player_1.lives++;
        control_led_line(get_players_lives());
        add_heart();
    }
}

void increment_players_score(int increment) { player_1.score += increment; }

void reset_player(void)
{
    reset_player_width();
    player_1.x = LCD_WIDTH / 2;
    player_1.y = LCD_HEIGHT - 50;
    player_1.score = 0;
    player_1.lives = 4;
}

int get_players_score(void) { return player_1.score; }

void decrement_players_lives(void)
{
    player_1.lives--;
    remove_heart();
    control_led_line(get_players_lives());
    reset_player_width();
    turn_on_RGB(RED, 1);
}

player get_player_stats(void) { return player_1; }

void enlarge_player(void) { player_1.width += 20; }

void reset_player_width(void) { player_1.width = player_1.max_width; }

void draw_player_score(void)
{
    char score_text[250];
    sprintf(score_text, "SCORE: %d", player_1.score);
    draw_text(score_text, 25, 12, 2, 2, 0xffff, true);
}

void draw_hearts(void)
{
    for (int i = 0; i < player_1.lives; ++i) {
        draw_char(220 + i * 20, 10, 3, 2, 2, 0xf800, true);
    }
}

void remove_heart(void) { draw_char(220 + player_1.lives * 20, 10, 3, 2, 2, 0xffff, true); }

void add_heart(void) { draw_char(220 + (player_1.lives - 1) * 20, 10, 3, 2, 2, 0xf800, true); }

void draw_difficulity(void)
{
    char difficulity[40];
    switch (GAME_STATS.difficulity) {
    case 1:
        sprintf(difficulity, "EASY");
        break;
    case 2:
        sprintf(difficulity, "MEDIUM");
        break;
    case 3:
        sprintf(difficulity, "HARD");
        break;
    default:
        fprintf(stderr, "ERROR: Wrong difficulity set, could not draw on screen.\n");
        break;
    }
    draw_text(difficulity, 360, 10, 2, 2, 0xffff, true);
}

void change_player_stats(void)
{
    switch (GAME_STATS.difficulity) {
    case 1:
        player_1.max_speed = 8;
        player_1.width = 100;
        player_1.max_width = 100;
        change_ball_speed(7);
        break;
    case 2:
        player_1.max_speed = 7;
        player_1.width = 80;
        player_1.max_width = 80;
        change_ball_speed(8);
        break;
    case 3:
        player_1.max_speed = 6;
        player_1.width = 70;
        player_1.max_width = 70;
        change_ball_speed(9);
        break;
    default:
        break;
    }
}
