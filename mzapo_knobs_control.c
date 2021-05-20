#include <stdint.h>
#include <stdio.h>

#include "mzapo_knobs_control.h"
#include "player.h"

int previous_value;
// bool near_edge;

void init_player_knobs(unsigned char *mem_base) { previous_value = *(volatile uint32_t *)(mem_base + SPILED_REG_KNOBS_8BIT_o); }

void control_player_knobs(unsigned char *mem_base, unsigned char *mem_base_lcd)
{
    uint32_t rgb_knobs_value;
    int new_value;
    rgb_knobs_value = *(volatile uint32_t *)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    new_value = (rgb_knobs_value >> 16) & 0x00ff;
    if (new_value > previous_value) {
        move_player(mem_base_lcd, -5);
    } else if (new_value < previous_value) {
        move_player(mem_base_lcd, 5);
    }
    previous_value = new_value;
}