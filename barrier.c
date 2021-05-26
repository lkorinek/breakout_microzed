#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>

#include "mzapo_lcd_control.h"

#include "mzapo_consts.h"
#include "mzapo_led_control.h"

#include "ball.h"
#include "barrier.h"
#include "player.h"

#define NUMBER_OF_BARRIERS_IN_ROW 5
#define NUMBER_OF_ROWS 6

barrier our_barriers[NUMBER_OF_BARRIERS_IN_ROW * NUMBER_OF_ROWS];

upgrade current_upgrade = {.x = 0, .y = 0, .type_upgrade = 0, .speed = 5, .falling_upgrade = false};

const unsigned short colors[] = {0xf800, 0xfD00, 0xffe0, 0x7e0, 0x3ff, 0xD017};

void init_barriers()
{
    int x = 0, y = TOP_SPACE + 10, shift = 5;
    for (int i = 0; i < NUMBER_OF_BARRIERS_IN_ROW * NUMBER_OF_ROWS; ++i) {
        our_barriers[i].x = x;
        our_barriers[i].y = y;
        our_barriers[i].height = 10;
        our_barriers[i].width = LCD_WIDTH / (NUMBER_OF_BARRIERS_IN_ROW)-shift;
        our_barriers[i].destroyed = false;
        x += our_barriers[i].width + shift;
        if (x >= (LCD_WIDTH - shift)) {
            x = 0;
            y += our_barriers[i].height + shift;
        }
    }
}

void update_barriers(unsigned char *parlcd_mem_base)
{
    bool barriers_present = false;
    int color_number = 0;
    for (int b = 0; b < NUMBER_OF_BARRIERS_IN_ROW * NUMBER_OF_ROWS; ++b) {
        if (b != 0 && b % NUMBER_OF_BARRIERS_IN_ROW == 0) {
            ++color_number;
        }
        for (int i = 0; i < our_barriers[b].width; ++i) {
            for (int j = 0; j < our_barriers[b].height; ++j) {
                if (!our_barriers[b].destroyed) {
                    set_display_data_pixel(parlcd_mem_base, our_barriers[b].x + i, our_barriers[b].y + j, colors[color_number]);
                    barriers_present = true;
                } else {
                    set_display_data_pixel(parlcd_mem_base, our_barriers[b].x + i, our_barriers[b].y + j, 0u);
                }
            }
        }
    }
    if (!barriers_present) { // end game, move to menu and reset game
        reset_upgrade();
        init_barriers();
        reset_player();
        reset_ball();
        change_ball_y_speed();
        GAME_STATS.menu = true;
        GAME_STATS.reset = true;
    }
}

void move_upgrade(unsigned char *parlcd_mem_base)
{
    player p_1 = get_player_stats();
    uint16_t color = 0u;
    if (current_upgrade.falling_upgrade) {
        switch (current_upgrade.type_upgrade) {
        case 3:
            color = 0xf800;
            break;
        case 36:
            color = 0xffe0;
            break;
        case 18:
            if (p_1.width == 100) {
                color = 0x6B4D;
            }
            break;
        default:
            break;
        }
        if (current_upgrade.y >= (LCD_HEIGHT - 16 * 2)) {
            draw_char(current_upgrade.x, current_upgrade.y, current_upgrade.type_upgrade, 2, 2, 0u, false);
            reset_upgrade();
        } else if (!GAME_STATS.freeze) {
            draw_char(current_upgrade.x, current_upgrade.y, current_upgrade.type_upgrade, 2, 2, 0u, false);
            current_upgrade.y += current_upgrade.speed;
            draw_char(current_upgrade.x, current_upgrade.y, current_upgrade.type_upgrade, 2, 2, color, false);
            if ((current_upgrade.x + char_width(2, current_upgrade.type_upgrade)) > p_1.x && (p_1.x + p_1.width) > current_upgrade.x &&
                (current_upgrade.y + 16) > p_1.y && (p_1.y + p_1.height) > current_upgrade.y) {
                switch (current_upgrade.type_upgrade) {
                case 3:
                    increment_players_lives();
                    turn_on_RGB(RED, 2);
                    break;
                case 36:
                    increment_players_score(50);
                    turn_on_RGB(YELLOW, 2);
                    break;
                case 18:
                    enlarge_player();
                    turn_on_RGB(BLUE, 2);
                    break;
                default:
                    break;
                }
                draw_char(current_upgrade.x, current_upgrade.y, current_upgrade.type_upgrade, 2, 2, 0u, false);
                reset_upgrade();
            }
        }
    }
}

void reset_upgrade()
{
    current_upgrade.falling_upgrade = false;
    current_upgrade.type_upgrade = 0;
    current_upgrade.x = 0;
    current_upgrade.y = 0;
}

void initialize_upgrade(int idx)
{
    current_upgrade.falling_upgrade = true;
    current_upgrade.x = our_barriers[idx].x + our_barriers[idx].width / 2;
    current_upgrade.y = our_barriers[idx].y;
}

bool bounce_from_barriers(int x, int y, int ball_w, int ball_h, unsigned char *parlcd_mem_base)
{
    bool ret = false;
    int upgrade = 0;
    time_t t;
    srand((unsigned)time(&t));
    for (int i = NUMBER_OF_BARRIERS_IN_ROW * NUMBER_OF_ROWS; i >= 0; --i) {
        if ((x + ball_w) > (our_barriers[i].x) && (our_barriers[i].x + our_barriers[i].width) > x && (y + ball_h) > our_barriers[i].y &&
            (our_barriers[i].y + our_barriers[i].height) > y && !our_barriers[i].destroyed) {
            ret = true;
            turn_on_RGB(GREEN, 1);
            our_barriers[i].destroyed = true;
            upgrade = rand() % 200;
            if (upgrade < 10 && !current_upgrade.falling_upgrade) { // Hearts
                initialize_upgrade(i);
                current_upgrade.type_upgrade = 3;
            } else if (upgrade < 50 && !current_upgrade.falling_upgrade) { // Enlargment
                initialize_upgrade(i);
                current_upgrade.type_upgrade = 18;
            } else if (!current_upgrade.falling_upgrade) { // Score
                initialize_upgrade(i);
                current_upgrade.type_upgrade = 36;
            }
            increment_players_score(10);
            update_barriers(parlcd_mem_base);
            break;
        }
    }
    return ret;
}
