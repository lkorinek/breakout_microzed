/*******************************************************************
  Main function for the Atari Breakout Game on MicroZed
  based MZ_APO board designed Lukáš Kořínek and Radek Chládek.

  breakout.c      - main file

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz, chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#define _POSIX_C_SOURCE 200112L

#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "ball.h"
#include "mzapo_consts.h"
#include "mzapo_lcd_control.h"
#include "mzapo_led_control.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "player.h"
#include "terminal.h"
#include "threads.h"

// global information about state of the game
game_settings GAME_STATS = {
    .menu = true,
    .reset = false,
    .exit = false,
    .difficulity = 1,
    .controls = false,
    .demo_mode = false,
    .freeze = false,
};

int main(int argc, char *argv[])
{
    // Setup terminal.
    set_terminal_raw(true);

    printf("Breakout started!\n");

    // Turn LEDs on at the start.
    control_led_line(4);
    turn_on_RGB(BLUE, 1);
    turn_on_RGB(BLUE, 2);

    shared_data data = init_shared_data();
    extern pthread_mutex_t mtx;
    extern pthread_cond_t convar;
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&convar, NULL);

    // Create threads.
    pthread_t thrs[THREAD_COUNT];
    pthread_create(&thrs[0], NULL, input_thread, &data);
    pthread_create(&thrs[1], NULL, output_thread, &data);
    pthread_create(&thrs[2], NULL, display_thread, &data);
    pthread_create(&thrs[3], NULL, periphery_thread, &data);

    // Join threads.
    for (int i = 0; i < THREAD_COUNT; ++i) {
        pthread_join(thrs[i], NULL);
    }

    // Reset terminal settings.
    set_terminal_raw(false);

    // Turn LEDs off the end.
    turn_off_RGB(1);
    turn_off_RGB(2);
    control_led_line(0);
    printf("\nGoodbye!\n");

    return 0;
}
