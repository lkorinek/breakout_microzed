Program Version 1.0 29/04/2021

##### Usage notes
***************
controls: 
arguments with start: 
control prints: 
***************
# Atari breakout
Classical retro game atari breakout implemented on the MicroZed APO. This project is realized as a semestral project for the course "Computer Architecture". 
May it get as many points as possible and possibly some joy for others :-). 
#### Used functions and files:
Here is the list of files and functions within these files we implemented and used.
***
#### mzapo_led_controls.c/h
file for control functions for RGB and led line
consts: RED, GREEN, BLUE -- colors for functions
###### 1.turn_on_RGB(color,RGB)
this function turns on rgb with specified color in format 0x000000; rgb can be within range 1-2  
input arguments: (volatile uint32_t)color- specified color that you wanna use; (int)RGB - which RGB you wanna turn on
output: none
###### 2.turn_off_RGB(rgb)
this function turns off specified RGB
input arguments: (int)rgb - which rgb should turn off
output: none
###### 3.led_line(lifes)
this functions turns on spicified part of led line -- mainly used for showing the number of life that player has left
input arguments: (int)lifes - number of lifes you wanna your player to have
output: 0 on succes -1 on the invalid input
***

##### Contact info:
Chládek Radek : chladrad@fel.cvut.cz
Kořínek Lukáš : korinlu1@fel.cvut.cz
##### License
(C) Copyright 2021 by Lukáš Kořínek and Radek Chládek
license:  any combination of GPL, LGPL, MPL or BSD licenses
