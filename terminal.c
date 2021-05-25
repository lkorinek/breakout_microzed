#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

#include "menu.h"
#include "player.h"
#include "terminal.h"

#define ENTER 13
#define ESC 27

void set_terminal_raw(bool set)
{
    static struct termios tio, tio_old;
    tcgetattr(STDIN_FILENO, &tio);
    if (set) {
        tio_old = tio;
        cfmakeraw(&tio);
        tio.c_lflag &= ~ECHO;
        tio.c_oflag |= OPOST;
        tio.c_lflag &= ~(ICANON);
        tio.c_cc[VMIN] = 0;
        tio.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &tio);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &tio_old);
    }
}

char get_terminal_input(void)
{
    char c;
    int r = read(0, &c, 1);

    int speed = 8;
    if (!GAME_STATS.controls && r > 0) {
        switch (c) {
        case 'a':
            set_player_speed(-get_player_max_speed());
            break;
        case 'w':
            if (GAME_STATS.menu) {
                change_menu_state(-1);
            }
            break;
        case 'd':
            set_player_speed(get_player_max_speed());
            break;
        case 's':
            if (GAME_STATS.menu) {
                change_menu_state(1);
            } else {
                set_player_speed(0);
            }
            break;
        case 'f':
            GAME_STATS.freeze = !GAME_STATS.freeze;
            freeze_ball(GAME_STATS.freeze);
            break;
        case ENTER:
            if (GAME_STATS.menu) {
                forward_selected_option_menu();
            }
            break;
        case ESC:
            if (GAME_STATS.menu) {
                reset_menu();
            }
            break;
        default:
            break;
        }
    }
    return c;
}