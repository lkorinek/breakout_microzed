/**
  mzapo_knobs_control.h      - functions to control lcd output on MZAPO

  (C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
      e-mail:   korinlu1@fel.cvut.cz chladrad@fel.cvut.cz
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 **/

#ifndef MZAPO_KNOBS_CONTROL
#define MZAPO_KNOBS_CONTROL

#define SPILED_REG_KBDRD_KNOBS_DIRECT_o 0x020
#define SPILED_REG_KNOBS_8BIT_o 0x024

void init_red_knobs(unsigned char *mem_base);
void control_red_knob(unsigned char *mem_base, unsigned char *mem_base_lcd);
void control_pause_knob(unsigned char *mem_base);

#endif