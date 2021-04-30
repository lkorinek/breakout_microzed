#include <stdbool.h>

#include "mzapo_lcd_control.h"

#include "mzapo_consts.h"
#include "player.h"

static player player_1 = {.x = LCD_WIDTH / 2 - 50, .y = LCD_HEIGHT - 40, .height = 14, .width = 100, .lives = 4};

void draw_player(unsigned char *parlcd_mem_base)
{
    remove_player(parlcd_mem_base);
    if (player_1.speed != 0) {
        move_player(parlcd_mem_base, player_1.speed);
    }

    for (int i = 0; i < player_1.width; ++i) {
        for (int j = 0; j < player_1.height; ++j) {
            set_display_data_pixel(parlcd_mem_base, player_1.x + i, player_1.y + j, 0xfff);
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
                set_display_data_pixel(parlcd_mem_base, player_1.x + i + x_move, player_1.y + j, 0xfff);
            }
        }
        player_1.x += x_move;
    }
}

int get_players_lives() { return player_1.lives; }

void decrement_players_lives() { player_1.lives--; }

player get_player_stats() {
    return player_1;
}