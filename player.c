#include "mzapo_lcd_control.h"

#include "mzapo_consts.h"
#include "player.h"

static player player_1 = {.x = LCD_WIDTH / 2 - 50, .y = LCD_HEIGHT - 40, .height = 14, .width = 100, .lives = 4};

void draw_player()
{
    remove_player();
    if (player_1.speed != 0) {
        move_player_x(player_1.speed);
    }

    for (int i = 0; i < player_1.width; ++i) {
        for (int j = 0; j < player_1.height; ++j) {
            set_display_data_pixel(player_1.x + i, player_1.y + j, 0xfff);
        }
    }
}

void remove_player()
{
    for (int i = 0; i < player_1.width; ++i) {
        for (int j = 0; j < player_1.height; ++j) {
            set_display_data_pixel(player_1.x + i, player_1.y + j, 0u);
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

void move_player(int x_move)
{
    if (player_1.x + player_1.width < LCD_WIDTH && player_1.x > 0) {
        remove_player();
        for (int i = 0; i < player_1.width; ++i) {
            for (int j = 0; j < player_1.height; ++j) {
                set_display_data_pixel(player_1.x + i + x_move, player_1.y + j, 0xfff);
            }
        }
        player_1.x += x_move;
    }
}