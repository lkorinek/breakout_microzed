#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "ball.h"
#include "barrier.h"
#include "menu.h"
#include "mzapo_knobs_control.h"
#include "mzapo_lcd_control.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "player.h"
#include "terminal.h"
#include "threads.h"

pthread_mutex_t mtx;
pthread_cond_t convar;

shared_data init_shared_data(void)
{
    shared_data ret;
    ret.run = true;
    ret.last_char = '\0';
    ret.parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    ret.spiled_mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    return ret;
}

void *input_thread(void *v)
{
    shared_data *data = (shared_data *)v;
    bool run = true;

    while (run) {
        char c = get_terminal_input();
        if (c == 'q') {
            pthread_mutex_lock(&mtx);
            data->last_char = c;
            data->run = false;
            pthread_mutex_unlock(&mtx);
        }

        pthread_mutex_lock(&mtx);
        run = data->run;
        pthread_mutex_unlock(&mtx);
    }

    return 0;
}

void *output_thread(void *v)
{
    shared_data *data = (shared_data *)v;
    bool run = true;

    while (run) {
        pthread_mutex_lock(&mtx);
        char c = data->last_char;
        pthread_mutex_unlock(&mtx);

        // TODO: send message
        printf("\rPressed button: %c Lives: %d SCORE: %d", c, get_players_lives(), get_players_score());
        fflush(stdout);

        if (get_players_lives() == 0) {
            // TODO: add some function game_over, which will print on screen GAME OVER
            fprintf(stderr, "\r\nGAME OVER!");
            pthread_mutex_lock(&mtx);
            data->run = false;
            pthread_mutex_unlock(&mtx);
        }

        pthread_mutex_lock(&mtx);
        run = data->run;
        pthread_mutex_unlock(&mtx);
    }

    // Make screen black at the end
    return 0;
}

void *display_thread(void *v)
{
    shared_data *data = (shared_data *)v;
    bool run = true;

    // Initialize LCD display
    unsigned char *parlcd_mem_base = data->parlcd_mem_base;
    init_parlcd(parlcd_mem_base);

    // Menu
    pthread_mutex_lock(&mtx);
    pthread_cond_broadcast(&convar);
    pthread_mutex_unlock(&mtx);
    draw_menu(parlcd_mem_base, data);
    pthread_mutex_lock(&mtx);
    run = data->run;
    pthread_mutex_unlock(&mtx);

    // Game
    init_barriers();
    draw_top_line(parlcd_mem_base);
    update_barriers(parlcd_mem_base);
    draw_difficulity();

    // Init game
    draw_hearts();

    while (run) {
        move_upgrade(parlcd_mem_base);
        move_ball(parlcd_mem_base);
        draw_player(parlcd_mem_base);
        draw_player_score();

        // Draw new data onto display
        draw_display_data(parlcd_mem_base);
        
        if (GAME_STATS.menu) { // move to mennu
            draw_menu(parlcd_mem_base, data);
        }
        
        pthread_mutex_lock(&mtx);
        run = data->run;
        pthread_mutex_unlock(&mtx);
    }

    game_over_screen(parlcd_mem_base);
    draw_display_data(parlcd_mem_base);
    sleep(5);

    // Make screen black at the end
    draw_black_screen(parlcd_mem_base);
    return 0;
}

void *compute_thread(void *v)
{
    shared_data *data = (shared_data *)v;
    bool run = true;
    init_red_knobs(data->parlcd_mem_base);
    pthread_mutex_lock(&mtx);
    pthread_cond_wait(&convar, &mtx);
    pthread_mutex_unlock(&mtx);
    while (run) {
        struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 5 * 1000 * 1000};
        control_red_knob(data->spiled_mem_base, data->parlcd_mem_base);
        control_pause_knob(data->spiled_mem_base);

        pthread_mutex_lock(&mtx);
        run = data->run;
        pthread_mutex_unlock(&mtx);

        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }

    return 0;
}