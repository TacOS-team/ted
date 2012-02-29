#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <file.h>
#include <tty.h>

typedef enum {
    STATE_EDIT,
    STATE_VIEW,
    STATE_QUIT
}state_t;

static state_t state = STATE_VIEW;

void clear_screen() {
    printf("\033[2J");
    fflush(stdout);
}

void get_command(file_t* file) {
    char c;
    clear_screen();
    tty_update_winsize();
    display_file(file);

    c = getchar();
    switch(c) {
        case 'x':
            state = STATE_QUIT;
            break;
        case 'i':
            state = STATE_EDIT;
            break;
        case 'z':
            cursor_up(file);
            break;
        case 'q':
            cursor_left(file);
            break; 
        case 's':
            cursor_down(file);
            break;
        case 'd':
            cursor_right(file);
            break;
        default: break;
    }
}

int main(int argc,char** argv) {
    file_t* file = NULL;

    if(argc>1)    
        file = load_file(argv[1]);
    else {
        printf("Bad parameter\n");
        return 0;
    }

    tty_raw();
    
    clear_screen();
    while(1) {
        switch(state) {
            case STATE_VIEW:
                get_command(file);
                break;
            case STATE_QUIT:
            case STATE_EDIT:
            default:
                exit(-1);
                break;
        }
    }
    return 0;
}
