#ifndef _LINE_H
#define _LINE_H

typedef struct _line_t{
    struct _line_t* prev;
    struct _line_t* next;
    char* data;
    unsigned int num;
    unsigned int llen; /* Number of charaters in the line */
    unsigned int lalloc; /* Memory allocated to the line */
}line_t;

unsigned int line_nb_wraps(line_t* line, unsigned int nb_col);

int print_line(line_t* line, int nb_lines, unsigned int nb_col);

#endif /* _LINE_H */
