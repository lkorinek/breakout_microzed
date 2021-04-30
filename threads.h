/**
  player.h      - functions to create and interact with players

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
} shared_data;

shared_data init_shared_data(void);
void *input_thread(void *v);
void *output_thread(void *v);
void *display_thread(void *v);
void *compute_thread(void *v);

#endif