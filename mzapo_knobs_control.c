#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "ball.h"
#include "menu.h"
#include "mzapo_knobs_control.h"
#include "player.h"

int previous_value_red;
bool freeze = false;
bool pressed = false;

void init_red_knobs(unsigned char *mem_base)
{
    uint32_t rgb_knobs_value = *(volatile uint32_t *)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    previous_value_red = (rgb_knobs_value >> 16) & 0x00ff;
}

void control_red_knob(unsigned char *mem_base, unsigned char *mem_base_lcd)
{
    int new_value;
    uint32_t rgb_knobs_value = *(volatile uint32_t *)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    new_value = (rgb_knobs_value >> 16) & 0x00ff;
    if (!freeze && !GAME_STATS.menu) {
        if (new_value > previous_value_red) {
            move_player(mem_base_lcd, -5);
        } else if (new_value < previous_value_red) {
            move_player(mem_base_lcd, 5);
        }
        previous_value_red = new_value;
    } else if (GAME_STATS.menu) {
        if (new_value - 3 > previous_value_red) {
            change_menu_state(-1);
            previous_value_red = new_value;
        } else if (new_value + 3 < previous_value_red) {
            change_menu_state(1);
            previous_value_red = new_value;
        }
    }
}

void control_pause_knob(unsigned char *mem_base)
{
    uint32_t rgb_knobs_value = *(volatile uint32_t *)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    int value = (rgb_knobs_value >> 24) & 0x0f;

    if (value == 1 && !pressed) {
        freeze = !freeze;
        pressed = true;
        freeze_ball(freeze);
    } else if (value == 0) {
        pressed = false;
    }
}