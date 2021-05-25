#include <pthread.h>
#include <stdbool.h>
#include <string.h>

#include "menu.h"

#include "mzapo_consts.h"
#include "mzapo_lcd_control.h"
#include "player.h"
#include "threads.h"

extern pthread_mutex_t mtx;

menu_stats menu = {
    .menu_selected = 0,
    .menu_selected_max = 4,
    .run = true,
    .credits = false,
    .settings = false,
    .settings_selected = 0,
    .settings_selected_max = 5,
    .change_color = false,
};

void draw_menu(unsigned char *parlcd_mem_base, shared_data *data)
{
    menu.run = true;
    while (GAME_STATS.menu && menu.run) {

        set_display_data_color(parlcd_mem_base, 0u);
        if (menu.settings) {
            draw_menu_settings(parlcd_mem_base);
        } else if (menu.credits) {
            draw_menu_credits(parlcd_mem_base);
        } else {
            draw_menu_box(parlcd_mem_base);
            draw_menu_options();
        }

        // Draw new data onto display
        draw_display_data(parlcd_mem_base);

        pthread_mutex_lock(&mtx);
        menu.run = data->run && menu.run && !GAME_STATS.exit;
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
    if (menu.settings) {
        switch (menu.settings_selected) {
        case 0: // Controls
            GAME_STATS.controls = !GAME_STATS.controls;
            break;
        case 1: // Difficulity
            ++GAME_STATS.difficulity;
            if (GAME_STATS.difficulity > 2) {
                GAME_STATS.difficulity = 0;
            }
            change_player_stats();
            break;
        case 2: // Mode - Human or Demo
            ++GAME_STATS.mode;
            if (GAME_STATS.mode > 1) {
                GAME_STATS.mode = 0;
            }
            break;
        case 3: // Color of player
            menu.change_color = !menu.change_color;
            break;
        default:
            break;
        }
    } else {
        switch (menu.menu_selected) {
        case 0:
            GAME_STATS.menu = false;
            menu.run = false;
            break;
        case 1:
            menu.settings = true;
            break;
        case 2:
            menu.credits = true;
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
        draw_menu_text(LCD_HEIGHT / 8 + 70 + 50 * i, texts[i], menu.menu_selected == i);
    }
}

void change_menu_state(int increment)
{
    if (menu.change_color) {
        change_player_color();
    } else if (menu.settings) {
        if (menu.settings_selected + increment < menu.settings_selected_max && menu.settings_selected + increment >= 0) {
            menu.settings_selected += increment;
        }
    } else {
        if (menu.menu_selected + increment < menu.menu_selected_max && menu.menu_selected + increment >= 0) {
            menu.menu_selected += increment;
        }
    }
}

void reset_menu(void)
{
    menu.credits = false;
    menu.settings = false;
    GAME_STATS.menu = true;
}

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
    draw_text("  SETTINGS", LCD_WIDTH / 5 + 24, 10, 3, 1, 0xffff, true);

    int texts_num = 3;
    char *texts[][3] = {{"PERIPHERY", "KEYBOARD"}, {"EASY", "MEDIUM", "HARD"}, {"HUMAN", "DEMO"}};

    int secod_idx = 0;

    for (int i = 0; i < texts_num; ++i) {
        if (!GAME_STATS.controls && i == 0) {
            secod_idx = 1;
        }
        if (i == 1) {
            secod_idx = GAME_STATS.difficulity;
        } else if (i == 2) {
            secod_idx = GAME_STATS.mode;
        }
        draw_menu_text(LCD_HEIGHT / 8 + 20 + 50 * i, texts[i][secod_idx], menu.settings_selected == i);
        secod_idx = 0;
    }

    // Pick a player color
    if (menu.settings_selected == 3) {
        draw_char(LCD_WIDTH / 2 - 20 - 8 * 5, LCD_HEIGHT / 8 + 154, 27, 5, 2, 0u, false);
        draw_char(LCD_WIDTH / 2 + 20 + 5, LCD_HEIGHT / 8 + 154, 26, 5, 2, 0u, false);
    }
    for (int i = LCD_HEIGHT / 8 + 170; i < LCD_HEIGHT / 8 + 210; ++i) {
        for (int j = LCD_WIDTH / 2 - 20; j < LCD_WIDTH / 2 + 20; ++j) {
            set_display_data_pixel(parlcd_mem_base, j, i, get_player_color());
        }
    }
}

void draw_menu_text(int y, char *text, bool selected)
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