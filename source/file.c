#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termio.h>

#include <file.h>
#include <tty.h>

#define MAX(X,Y) ((X>Y)?(X):(Y))
#define MIN(X,Y) ((X>Y)?(Y):(X))

file_t* load_file(char* file) {
    char c;
    unsigned int count;
    file_t* new_file;
    fpos_t pos;
    unsigned int num = 0;

    /* File structure initialization */
    new_file = malloc(sizeof(file_t));
    new_file->head = NULL;
    new_file->tail = NULL;
    new_file->c = 1;
    new_file->line_count = 0;

    /* Open file descriptor */
    new_file->fd = fopen(file, "rw");    

    c=0;
    while(c!=EOF){
        /* Save current position */
        fgetpos(new_file->fd, &pos);
        
        count = 0;
        do {
            c = fgetc(new_file->fd);
            count++;
        }while(c!='\n' && c!='\0' && c!=EOF);

        if(c != EOF) {
            num++;
            if(new_file->head == NULL) { /* Si c'est la première ligne qu'on ajoute... */
                new_file->head = malloc(sizeof(line_t));
                new_file->tail = new_file->head;
                new_file->tail->prev = NULL;
                new_file->tail->next = NULL;

                /* First line added, we shall also initialize the auxiliary pointers */
                new_file->current = new_file->head;
                new_file->top = new_file->head;
            } else {
                line_t* aux = malloc(sizeof(line_t));
                aux->prev = new_file->tail;
                aux->next = NULL;
                new_file->tail->next = aux;
                new_file->tail = aux;
            }
            new_file->tail->data = malloc(sizeof(char)*count+1); /* strlen + '\0' */
            new_file->tail->lalloc = sizeof(char)*count+1;
            new_file->tail->num = num;
            /* Load saved position */
            fsetpos(new_file->fd, &pos);

            /* Read the line */
            fread(new_file->tail->data, count, sizeof(char), new_file->fd);
            new_file->tail->llen = strlen(new_file->tail->data);
            
        }
    }

    new_file->line_count = num;
    return new_file;
}

void display_file(file_t* file) {
    line_t* aux = file->top;
    unsigned int count = tty_row()-1;

    printf("\033[0;0H");
    fflush(stdout);

    while(aux != NULL && count > 0) {
        count -= print_line(aux, count, tty_col());
        aux = aux->next;
    }
    printf("\033[%d;0H %d,%d", tty_row(), file->c, file->current->num);
    show_cursor(file);
    fflush(stdout);
}

void show_cursor(file_t* file) {
    line_t* line = file->top;
    int row = 1;
    int col;

    while(line->num < file->current->num && line->next != NULL) {
        row += line_nb_wraps(line, tty_col())+1;
        line = line->next;    
    }
    row += MIN(file->c,line->llen) / tty_col();
    col = MIN(file->c,line->llen)  % tty_col();
    printf("\033[%d;%dH",row, col);
    fflush(stdout); 
}

void scroll_down(file_t* file, unsigned int n) {
    int i = 0;
    while(file->top->next != NULL && i<n) {
        file->top = file->top->next;
        i++;
    }
}

void scroll_up(file_t* file, unsigned int n) {
    int i = 0;
    while(file->top->prev != NULL && i<n) {
        file->top = file->top->prev;
        i++;
    }
}

void cursor_down(file_t* file) {
    if(file->current->next != NULL) {
        file->current = file->current->next;
        if(file->current->num-file->top->num >= tty_row()-1) {
            scroll_down(file, 1);
        }
    }
}

void cursor_up(file_t* file) {
    if(file->current->prev != NULL) {
        if(file->current->num == file->top->num) {
            scroll_up(file,1);
        }
        
        file->current = file->current->prev;

    }
}

void cursor_right(file_t* file) {
    if(file->c < file->current->llen-1)
        file->c++;
}

void cursor_left(file_t* file) {
    if(file->c > 1)
        file->c--;
}
