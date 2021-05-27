/**
  threads.h      - game threads, core of the game

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef THREADS
#define THREADS

#include <pthread.h>

#define THREAD_COUNT 4

typedef struct {
    bool run;
    char last_char;
    unsigned char *parlcd_mem_base;
    unsigned char *spiled_mem_base;
} shared_data;

shared_data init_shared_data(void);

/*
 * Input thread to recieve input from keyboard.
 */
void *input_thread(void *v);

/*
 * Output thread to print output to terminal.
 */
void *output_thread(void *v);

/*
 * Display thread to display data on screen.
 */
void *display_thread(void *v);

/*
 * Periphery thread to recieve input from periphery knobs.
 */
void *periphery_thread(void *v);

#endif