#include <stdio.h>
#include <line.h>

/* Returns the number of line wraps necessary to print full line */
unsigned int line_nb_wraps(line_t* line, unsigned int nb_col) {
    return (line->llen / nb_col);
}

int print_line(line_t* line, int nb_lines, unsigned int nb_col) {
    int needed_lines = line_nb_wraps(line, nb_col) + 1;
    int i,j;
    char* aux;

    /* If enough wraps are allowed, just print the whole line */
    if(needed_lines <= nb_lines) {
        printf("%s", line->data);
        return needed_lines;
    } else {
        aux = line->data;
        for(i=0; i<nb_lines; i++) {
            j=0;
            do {
                putchar(*aux);
                aux++;
                j++;
            }while(*aux != '\n' && j<nb_col);
        }
        fflush(stdout);
        return nb_lines;
    }
}

