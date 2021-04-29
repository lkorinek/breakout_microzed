/**
  mzapo_consts.h      -constants we are using

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

// mainly for mzapo_led_functions
#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff
#define SPILED_MEM_BASE map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0)
