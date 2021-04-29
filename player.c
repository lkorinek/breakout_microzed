#include "mzapo_lcd_control.h"

#include "player.h"

static player player_1 = {.x = LCD_WIDTH / 2 - 50, .y = LCD_HEIGHT - 40, .height = 16, .width = 100, .lives = 4};

void draw_player()
{
    remove_player();
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

void move_player_x(int x_move)
{
    remove_player();
    for (int i = 0; i < player_1.width; ++i) {
        for (int j = 0; j < player_1.height; ++j) {
            set_display_data_pixel(player_1.x + i + x_move, player_1.y + j, 0xfff);
        }
    }
    player_1.x += x_move;
}

void move_player_y(int y_move)
{
    remove_player();
    for (int i = 0; i < player_1.width; ++i) {
        for (int j = 0; j < player_1.height; ++j) {
            set_display_data_pixel(player_1.x + i, player_1.y + j + y_move, 0xfff);
        }
    }
    player_1.y += y_move;
}