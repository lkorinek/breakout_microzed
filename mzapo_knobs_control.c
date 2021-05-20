#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "ball.h"
#include "mzapo_knobs_control.h"
#include "player.h"

int previous_value;
bool freeze = false;
bool pressed = false;

void init_player_knobs(unsigned char *mem_base) { previous_value = *(volatile uint32_t *)(mem_base + SPILED_REG_KNOBS_8BIT_o); }

void control_player_knob(unsigned char *mem_base, unsigned char *mem_base_lcd)
{
    int new_value;
    uint32_t rgb_knobs_value = *(volatile uint32_t *)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    new_value = (rgb_knobs_value >> 16) & 0x00ff;
    if (!freeze) {
        if (new_value > previous_value) {
            move_player(mem_base_lcd, -5);
        } else if (new_value < previous_value) {
            move_player(mem_base_lcd, 5);
        }
    }

    previous_value = new_value;
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