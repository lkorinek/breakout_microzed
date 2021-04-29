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
    int x_move = 0;
    int y_move = 0;
    if (r > 0) {
        switch (c) {
        case 'w':
            y_move = 10;
            break;
        case 's':
            y_move = -10;
            break;
        case 'a':
            x_move = -10;
            break;
        case 'd':
            x_move = 10;
            break;
        default:
            break;
        }
    }
    if (x_move) {
        move_player_x(x_move);
    } else if (y_move) {
        move_player_y(y_move);
    }
    return c;
}