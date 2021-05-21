#include <pthread.h>
#include <stdbool.h>

#include "menu.h"

#include "mzapo_consts.h"
#include "mzapo_lcd_control.h"
#include "threads.h"

extern pthread_mutex_t mtx;

int menu_selected = 0;
int menu_selected_max = 4;
bool run_menu = true;

void draw_menu(unsigned char *parlcd_mem_base, shared_data *data)
{
    draw_menu_box(parlcd_mem_base);

    while (GAME_STATS.menu && run_menu) {
        draw_menu_box(parlcd_mem_base);

        draw_menu_options();

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
    switch (menu_selected) {
    case 0:
        GAME_STATS.menu = false;
        run_menu = false;
        break;
    case 1:

        break;
    case 2:

        break;
    case 3:
        GAME_STATS.exit = true;
        break;
    default:
        break;
    }
}

void draw_menu_options(void)
{
    if (menu_selected == 0) {
        draw_text("START", LCD_WIDTH / 5 + 79, LCD_HEIGHT / 8 + 70, 3, 2, 0xffff, true);

    } else {
        draw_text("START", LCD_WIDTH / 5 + 79, LCD_HEIGHT / 8 + 70, 3, 2, 0u, false);
    }

    if (menu_selected == 1) {
        draw_text("SETTINGS", LCD_WIDTH / 5 + 42, LCD_HEIGHT / 8 + 120, 3, 2, 0xffff, true);

    } else {
        draw_text("SETTINGS", LCD_WIDTH / 5 + 42, LCD_HEIGHT / 8 + 120, 3, 2, 0u, false);
    }

    if (menu_selected == 2) {
        draw_text("CREDITS", LCD_WIDTH / 5 + 55, LCD_HEIGHT / 8 + 170, 3, 2, 0xffff, true);

    } else {
        draw_text("CREDITS", LCD_WIDTH / 5 + 55, LCD_HEIGHT / 8 + 170, 3, 2, 0u, false);
    }

    if (menu_selected == 3) {
        draw_text("EXIT", LCD_WIDTH / 5 + 95, LCD_HEIGHT / 8 + 220, 3, 2, 0xffff, true);
    } else {
        draw_text("EXIT", LCD_WIDTH / 5 + 95, LCD_HEIGHT / 8 + 220, 3, 2, 0u, false);
    }
}

void change_menu_state(int increment)
{
    if (menu_selected + increment < menu_selected_max && menu_selected + increment >= 0) {
        menu_selected += increment;
    }
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