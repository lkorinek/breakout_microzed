#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

#include "player.h"
#include "terminal.h"

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
            set_player_speed(-speed);
            break;
        case 'd':
            set_player_speed(speed);
            break;
        case 's':
            set_player_speed(0);
            break;
        default:
            break;
        }
    }
    return c;
}