#include <termio.h>
#include <unistd.h>

struct winsize ws;

void tty_raw() {
    struct termios newt;
    tcgetattr(STDIN_FILENO, &newt);
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void tty_update_winsize() {
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
}

unsigned int tty_col() {
	return ws.ws_col;
}

unsigned int tty_row() {
	return ws.ws_row;
}

