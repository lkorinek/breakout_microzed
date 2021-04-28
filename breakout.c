/*******************************************************************
  Main function for the Atari Breakout Game on MicroZed
  based MZ_APO board designed Lukáš Kořínek and Radek Chládek.

  breakout.c      - main file

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz, chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#define _POSIX_C_SOURCE 200112L

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "mzapo_consts.h"
#include "mzapo_led_functions.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

int main(int argc, char *argv[])
{
    printf("Hello world\n");

    sleep(4);

    printf("Goodbye world\n");

    return 0;
}