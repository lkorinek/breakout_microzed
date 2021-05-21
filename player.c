#include <stdbool.h>
#include <stdio.h>

#include "mzapo_lcd_control.h"

#include "mzapo_consts.h"
#include "player.h"

static player player_1 = {.x = LCD_WIDTH / 2 - 50, .y = LCD_HEIGHT - 40, .height = 11, .width = 100, .lives = 4, .score = 0};

void draw_player(unsigned char *parlcd_mem_base)
{
    remove_player(parlcd_mem_base);
    if (player_1.speed != 0) {
        move_player(parlcd_mem_base, player_1.speed);
    }

    for (int i = 0; i < player_1.width; ++i) {
        for (int j = 0; j < player_1.height; ++j) {
            set_display_data_pixel(parlcd_mem_base, player_1.x + i, player_1.y + j, 0xf80b);
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

void decrement_player_speed()
{
    if (player_1.speed > 0) {
        player_1.speed -= 1;
    } else if (player_1.speed < 0) {
        player_1.speed += 1;
    }
}

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
        for (int i = 0; i < player_1.width; ++i) {
            for (int j = 0; j < player_1.height; ++j) {
                set_display_data_pixel(parlcd_mem_base, player_1.x + i + x_move, player_1.y + j, 0xf80b);
            }
        }
        player_1.x += x_move;
    }
}

int get_players_lives() { return player_1.lives; }

void increment_players_lives()
{
    if (player_1.lives < 4) {
        player_1.lives++;
    }
}

void increment_players_score(int increment) { player_1.score += increment; }

int get_players_score() { return player_1.score; }

void decrement_players_lives()
{
    player_1.lives--;
    remove_heart();
}

player get_player_stats() { return player_1; }

void draw_player_score(void)
{
    char score_text[250];
    sprintf(score_text, "SCORE: %d", player_1.score);
    draw_text(score_text, 25, 12, 2, 2, 0xffff);
}

void draw_hearts(void)
{
    for (int i = 0; i < player_1.lives; ++i) {
        draw_char(220 + i * 20, 10, 3, 2, 2, 0xf800);
    }
}

void remove_heart(void) { draw_char(220 + player_1.lives * 20, 10, 3, 2, 2, 0xffff); }

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
    draw_text(difficulity, 360, 10, 2, 2, 0xffff);
}