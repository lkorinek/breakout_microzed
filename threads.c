#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

#include "ball.h"
#include "barrier.h"
#include "mzapo_lcd_control.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "player.h"
#include "terminal.h"
#include "threads.h"

pthread_mutex_t mtx;

shared_data init_shared_data(void)
{
    shared_data ret;
    ret.run = true;
    ret.last_char = '\0';
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
    unsigned char *parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    init_parlcd(parlcd_mem_base);
    draw_black_screen(parlcd_mem_base);
    init_barriers();
    draw_barriers(parlcd_mem_base);

    // Draw new data onto display
    draw_display_data(parlcd_mem_base);

    while (run) {
        draw_player(parlcd_mem_base);
        move_ball(parlcd_mem_base);

        // Draw new data onto display
        draw_display_data(parlcd_mem_base);

        pthread_mutex_lock(&mtx);
        run = data->run;
        pthread_mutex_unlock(&mtx);
    }

    // Make screen black at the end
    draw_black_screen(parlcd_mem_base);
    return 0;
}

void *compute_thread(void *v)
{
    shared_data *data = (shared_data *)v;
    bool run = true;

    while (run) {

        pthread_mutex_lock(&mtx);
        run = data->run;
        pthread_mutex_unlock(&mtx);
    }

    return 0;
}