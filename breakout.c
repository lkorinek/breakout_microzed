/*******************************************************************
  Main function for the Atari Breakout Game on MicroZed
  based MZ_APO board designed Lukáš Kořínek and Radek Chládek.

  breakout.c      - main file

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz, chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#define _POSIX_C_SOURCE 200112L

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "mzapo_consts.h"
#include "mzapo_lcd_control.h"
#include "mzapo_led_control.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "player.h"
#include "terminal.h"

int main(int argc, char *argv[])
{
    // Setup terminal
    set_terminal_raw(true);

    printf("Hello World!\n");

    // Initialize LCD display
    init_parlcd();
    draw_black_screen();

    struct timespec loop_delay;
    loop_delay.tv_sec = 0;
    loop_delay.tv_nsec = 150 * 1000 * 1000;

    bool run = true;
    while (run) {
        set_display_data_color(0u);
        draw_player();

        char c = get_terminal_input();
        if (c == 'q') {
            run = false;
        }

        // TODO: send message
        printf("\rPressed button: %c", c);
        fflush(stdout);

        // Draw new data onto display
        draw_display_data();

        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }

    // Make screen black at the end
    draw_black_screen();

    // Reset terminal settings
    set_terminal_raw(false);

    printf("\nGoodbye World!\n");

    return 0;
}