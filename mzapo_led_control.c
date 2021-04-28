#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

#include "mzapo_led_control.h"

void turn_on_RGB(volatile uint32_t color, int RGB)
{
    unsigned char *mem_base;
    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    // if mapping fails exit with error code
    if (mem_base == NULL) {
        exit(1);
    }

    *(volatile uint32_t *)(mem_base + (RGB == 1 ? SPILED_REG_LED_RGB1_o : SPILED_REG_LED_RGB2_o)) = color;
}

void turn_off_RGB(int RGB)
{
    unsigned char *mem_base;
    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    // if mapping fails exit with error code
    if (mem_base == NULL) {
        exit(1);
    }
    *(volatile uint32_t *)(mem_base + (RGB == 1 ? SPILED_REG_LED_RGB1_o : SPILED_REG_LED_RGB2_o)) = 0x000000;
}

bool control_led_line(int lifes)
{
    bool ret = true;
    unsigned char *mem_base;
    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);

    // if mapping fails exit with error code
    if (mem_base == NULL) {
        exit(1);
    }

    // number of lifes which is supposed to be turn on
    volatile uint32_t number = 0x00000000;

    switch (lifes) {
    case 0:
        number = 0x00000000;
        break;
    case 1:
        number = 0xff000000;
        break;
    case 2:
        number = 0xffff0000;
        break;
    case 3:
        number = 0xffffff00;
        break;
    case 4:
        number = 0xffffffff;
        break;
    default:
        ret = false;
        break;
    }

    *(volatile uint32_t *)(mem_base + SPILED_REG_LED_LINE_o) = number;

    return ret;
}
