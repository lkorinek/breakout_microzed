
#include <stdio.h>
#include <stdlib.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

void turn_on_RGB(volatile uint32_t color, int RGB)
{
    unsigned char *mem_base;
    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    // if mapping fails exit with error code
    if (mem_base == NULL) {
        exit(1);
    }

    *(volatile uint32_t *)(mem_base + (RGB == 1 ? SPILED_REG_LED_RGB1_o
                                                : SPILED_REG_LED_RGB2_o)) =
        color;
}

void turn_off_RGB(int RGB)
{
    unsigned char *mem_base;
    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    // if mapping fails exit with error code
    if (mem_base == NULL) {
        exit(1);
    }
    *(volatile uint32_t *)(mem_base + (RGB == 1 ? SPILED_REG_LED_RGB1_o
                                                : SPILED_REG_LED_RGB2_o)) =
        0x000000;
}
