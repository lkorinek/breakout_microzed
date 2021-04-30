#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

#include "terminal.h"
#include "player.h"
#include "mzapo_lcd_control.h"
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
        printf("\rPressed button: %c Lives: %d", c, get_players_lives());
        fflush(stdout);

        pthread_mutex_lock(&mtx);
        run = data->run;
        pthread_mutex_unlock(&mtx);
    }

    // Make screen black at the end
    draw_black_screen();
    return 0;
}

void *display_thread(void *v)
{
    shared_data *data = (shared_data *)v;
    bool run = true;

    // Initialize LCD display
    init_parlcd();
    draw_black_screen();

    while (run) {
        draw_player();

        // Draw new data onto display
        draw_display_data();

        pthread_mutex_lock(&mtx);
        run = data->run;
        pthread_mutex_unlock(&mtx);
    }

    // Make screen black at the end
    draw_black_screen();
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

    // Make screen black at the end
    draw_black_screen();
    return 0;
}