#include <pthread.h>
#include <stdbool.h>

#include "menu.h"

#include "mzapo_consts.h"
#include "mzapo_lcd_control.h"
#include "player.h"
#include "threads.h"

extern pthread_mutex_t mtx;

int menu_selected = 0;
int menu_selected_max = 4;
bool run_menu = true;
bool menu_credits = false;
bool menu_settings = false;
int settings_selected = 0;
int settings_selected_max = 5;
bool change_color = false;

void draw_menu(unsigned char *parlcd_mem_base, shared_data *data)
{
    run_menu = true;
    while (GAME_STATS.menu && run_menu) {

        set_display_data_color(parlcd_mem_base, 0u);
        if (menu_settings) {
            draw_menu_settings(parlcd_mem_base);
        } else if (menu_credits) {
            draw_menu_credits(parlcd_mem_base);
        } else {
            draw_menu_box(parlcd_mem_base);
            draw_menu_options();
        }

        // Draw new data onto display
        draw_display_data(parlcd_mem_base);

        pthread_mutex_lock(&mtx);
        run_menu = data->run && run_menu && !GAME_STATS.exit;
        pthread_mutex_unlock(&mtx);
    }
    set_display_data_color(parlcd_mem_base, 0u);
}

void draw_menu_box(unsigned char *parlcd_mem_base)
{
    for (int i = LCD_HEIGHT / 8; i < LCD_HEIGHT; ++i) {
        for (int j = LCD_WIDTH / 5; j < LCD_WIDTH - LCD_WIDTH / 5; ++j) {
            set_display_data_pixel(parlcd_mem_base, j, i, 0xffff);
        }
    }

    draw_text("  BREAKOUT", LCD_WIDTH / 5 + 12, LCD_HEIGHT / 8 + 10, 3, 1, 0xffff, true);
}

void forward_selected_option_menu(void)
{
    if (menu_settings) {
        // number of players, difficulity, controls, demo mode

        switch (settings_selected) {
        case 0:
            GAME_STATS.controls = !GAME_STATS.controls;
            break;
        case 1:
            ++GAME_STATS.difficulity;
            if (GAME_STATS.difficulity > 2) {
                GAME_STATS.difficulity = 0;
            }
            break;
        case 2:
            ++GAME_STATS.num_players;
            if (GAME_STATS.num_players > 1) {
                GAME_STATS.num_players = 0;
            }
            break;
        case 3:
            ++GAME_STATS.mode;
            if (GAME_STATS.mode > 1) {
                GAME_STATS.mode = 0;
            }
            break;
        case 4:
            change_color = !change_color;
            break;
        default:
            break;
        }
    } else {
        switch (menu_selected) {
        case 0:
            GAME_STATS.menu = false;
            run_menu = false;
            break;
        case 1:
            menu_settings = true;
            break;
        case 2:
            menu_credits = true;
            break;
        case 3:
            GAME_STATS.exit = true;
            break;
        default:
            break;
        }
    }
}

void draw_menu_options(void)
{
    int texts_num = 4;
    char *texts[] = {"START", "SETTINGS", "CREDITS", "EXIT"};

    for (int i = 0; i < texts_num; ++i) {
        draw_menu_text(LCD_HEIGHT / 8 + 70 + 50 * i, texts[i], menu_selected == i);
    }
}

void change_menu_state(int increment)
{
    if (change_color) {
        change_player_color();
    } else if (menu_settings) {
        if (settings_selected + increment < settings_selected_max && settings_selected + increment >= 0) {
            settings_selected += increment;
        }
    } else {
        if (menu_selected + increment < menu_selected_max && menu_selected + increment >= 0) {
            menu_selected += increment;
        }
    }
}

void reset_menu(void)
{
    menu_credits = false;
    menu_settings = false;
    GAME_STATS.menu = true;
}

// void move_ball(unsigned char *parlcd_mem_base)
// {
//     delete_ball(parlcd_mem_base);

//     if (ball_1.x >= LCD_WIDTH - ball_1.width || ball_1.x <= ball_1.width) {
//         ball_1.increment_x = -ball_1.increment_x;
//     }
//     if (ball_1.y <= ball_1.height + TOP_SPACE - 5 || ball_1.y >= LCD_HEIGHT - ball_1.height) {
//         ball_1.increment_y = -ball_1.increment_y;
//         if (ball_1.y >= LCD_HEIGHT - ball_1.height) {
//             decrement_players_lives();
//             control_led_line(get_players_lives());
//             reset_ball();
//         }
//     }

//     bounce_ball(parlcd_mem_base);

//     ball_1.x += ball_1.increment_x;
//     ball_1.y += ball_1.increment_y;

//     draw_ball(parlcd_mem_base);
// }

void game_over_screen(unsigned char *parlcd_mem_base)
{
    int scale = 11;
    set_display_data_color(parlcd_mem_base, 0u);
    draw_text("GAME", LCD_WIDTH / 2 - 16 * scale, 25, scale, 2, 0xffff, false);
    draw_text("OVER", LCD_WIDTH / 2 - 16 * scale, (16 * scale) - 25, scale, 2, 0xf800, false);
}

void draw_menu_credits(unsigned char *parlcd_mem_base)
{
    int shift = 10;
    int scale = 3;
    set_display_data_color(parlcd_mem_base, 0u);
    draw_text("MADE BY/AS:", LCD_WIDTH / 4 - (16 * scale) - 20, 25, scale, 2, 0xf800, false);
    scale = 2;
    draw_text("$ chladrad", LCD_WIDTH / 3 - 16 * scale, (16 * 5), scale, 2, 0xfD00, false);
    draw_text("$ korinlu1", LCD_WIDTH / 3 - 16 * scale, (16 * 5) + (16 * scale) + shift, scale, 2, 0xffe0, false);
    draw_text("As semestral project for APO", 16 * scale, (16 * 5) + (16 * scale) * 2 + shift, scale, 2, 0x7e0, false);
    draw_text("We hope you will enjoy it", 16 * scale, (16 * 5) + (16 * scale) * 3 + shift, scale, 2, 0x3ff, false);
    draw_text("Go play our awesome game !", 16 * scale, (16 * 5) + (16 * scale) * 4 + shift, scale, 2, 0xD017, false);
}

void draw_menu_settings(unsigned char *parlcd_mem_base)
{
    for (int i = 0; i < LCD_HEIGHT; ++i) {
        for (int j = LCD_WIDTH / 5; j < LCD_WIDTH - LCD_WIDTH / 5; ++j) {
            set_display_data_pixel(parlcd_mem_base, j, i, 0xffff);
        }
    }
    int scale = 3;
    draw_text("  SETTINGS", LCD_WIDTH / 5 + 24, 10, 3, 1, 0xffff, true);

    int texts_num = 4;
    char *texts[][3] = {{"PERIPHERY", "KEYBOARD"}, {"EASY", "MEDIUM", "HARD"}, {"ONE PLAYER", "TWO PLAYERS"}, {"HUMAN", "DEMO"}};

    int secod_idx = 0;

    for (int i = 0; i < texts_num; ++i) {
        if (GAME_STATS.controls && i == 0) {
            secod_idx = 1;
        }
        if (i == 1) {
            secod_idx = GAME_STATS.difficulity;
        } else if (i == 2) {
            secod_idx = GAME_STATS.num_players;
        } else if (i == 3) {
            secod_idx = GAME_STATS.mode;
        }
        draw_menu_text(LCD_HEIGHT / 8 + 20 + 50 * i, texts[i][secod_idx], settings_selected == i);
        secod_idx = 0;
    }

    if (settings_selected == 4) {
        draw_char(LCD_WIDTH / 2 - 20 - 8 * 5, LCD_HEIGHT / 8 + 204, 27, 5, 2, 0u, false);
        for (int i = LCD_HEIGHT / 8 + 220; i < LCD_HEIGHT / 8 + 260; ++i) {
            for (int j = LCD_WIDTH / 2 - 20; j < LCD_WIDTH / 2 + 20; ++j) {
                set_display_data_pixel(parlcd_mem_base, j, i, get_player_color());
            }
        }
        draw_char(LCD_WIDTH / 2 + 20 + 5, LCD_HEIGHT / 8 + 204, 26, 5, 2, 0u, false);
    } else {
        for (int i = LCD_HEIGHT / 8 + 220; i < LCD_HEIGHT / 8 + 260; ++i) {
            for (int j = LCD_WIDTH / 2 - 20; j < LCD_WIDTH / 2 + 20; ++j) {
                set_display_data_pixel(parlcd_mem_base, j, i, get_player_color());
            }
        }
    }
}

void draw_menu_text(int y, char *text, int selected)
{
    int scale = 3;
    int x = get_menu_position(text);
    if (selected) {
        draw_text(text, x, y, scale, 2, 0xffff, true);
    } else {
        draw_text(text, x, y, scale, 2, 0u, false);
    }
}

int get_menu_position(char *text)
{
    int width = LCD_WIDTH - 2 * LCD_WIDTH / 5;
    int length = strlen(text);
    int char_width = 8 * 3;
    return (LCD_WIDTH / 5) + (width - (length * char_width)) / 2;
}