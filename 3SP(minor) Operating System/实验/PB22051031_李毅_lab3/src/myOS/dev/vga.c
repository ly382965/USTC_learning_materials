#include "vga.h"
#include "io.h"
#include "uart.h"

int col = 0;
int row = 0;

void update_cursor(void)
{
    int position = col + row * VGA_COL;
    outb(0x3D4, 0x0F);
    outb(0x3D5, position);
    outb(0x3D4, 0x0E);
    outb(0x3D5, position >> 8);
}

void clear_screen(void)
{
    for (int* p = (int*)VGA_BASE; p < (int*)0xB8FA0; ++p) {
        *p = 0x07200720;
    }
}

void scroll_screen(void)
{
    long second_line = VGA_BASE + VGA_COL * 2;
    long last_line = VGA_BASE + VGA_COL * (VGA_ROW - 1) * 2;
    long end = last_line + VGA_COL * 2;
    for (int* p = (int*)VGA_BASE; p < (int*)end; ++p) {
        *(p - 0x28) = *p;
    }
    for (int* p = (int*)last_line; p < (int*)end; ++p) {
        *p = 0x07200720;
    }
}

void append_char_to_screen(char c, int color)
{
    if (c == '\n') {
        col = 0;
        if (row == (VGA_ROW - 1)) {
            scroll_screen();
        } else {
            row++;
        }
    } else {
        long offset = (row * VGA_COL + col) * 2;
        char* p = (char*)(VGA_BASE + offset);
        *p = c;
        p++;
        *p = (char)color;
        if (col == 79) {
            col = 0;
            if (row == (VGA_ROW - 1)) {
                scroll_screen();
            } else {
                row++;
            }
        } else {
            col++;
        }
    }
    update_cursor();
}

void append2screen(char* str, int color)
{
    for (char* p = str; *p != '\0'; ++p) {
        append_char_to_screen(*p, color);
    }
}

// put a single char to vga
void put_char2pos(unsigned char c, int color, int pos) {
    // put the char to cursor_pos
    unsigned char *address_writer8;
    address_writer8 = (unsigned char*)(VGA_BASE + pos * 2);
    *address_writer8 = c;
    address_writer8 = (unsigned char*)(VGA_BASE + pos * 2 + 1);
    *address_writer8 = (unsigned char)color;
}

// just put a string to a specific position, don't change cursor pos, ignore escape char like '\n'
void put_chars(char *str, int color, int line, int col) 
{
    int pos = line * VGA_COL + col;
    for (int i = 0; str[i] != '\0'; i++) 
    {
        put_char2pos(str[i], color, pos);
        pos++;
    }
}
