#ifndef _FILE_H
#define _FILE_H

#include <line.h>

typedef struct {
	
	FILE* fd;
	
    line_t* head; /* Pointer to the first line of the file */
    line_t* tail; /* Pointer to the last line of the file */

    line_t* current; /* Pointer to the current line of the file */
    unsigned int c;

    line_t* top; /* Pointer to the first line displayed on the screen */

    unsigned int line_count;
}file_t;

file_t* load_file(char* file);
void display_file(file_t* file);
void show_cursor(file_t* file);
void scroll_down(file_t* file, unsigned int n);
void scroll_up(file_t* file, unsigned int n);
void cursor_down(file_t* file);
void cursor_up(file_t* file);
void cursor_right(file_t* file);
void cursor_left(file_t* file);

#endif /* _FILE_H */
