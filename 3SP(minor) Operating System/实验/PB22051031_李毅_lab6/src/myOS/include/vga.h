#ifndef __VGA_H__
#define __VGA_H__

int put_chars(char *msg, char color, int _row, int _col);

void append2screen(char *str,int color);

void clear_screen(void);

#endif