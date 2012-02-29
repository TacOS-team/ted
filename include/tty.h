#ifndef _TTY_H
#define _TTY_H

void tty_raw();
void tty_update_winsize();

unsigned int tty_row();
unsigned int tty_col();

#endif /* _TTY_H */
