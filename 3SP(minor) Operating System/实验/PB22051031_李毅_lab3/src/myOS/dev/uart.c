#include "io.h"
#define uart_base 0x3F8

unsigned char uart_get_char(void)
{
	while (!(inb(uart_base+5)&1));
	return inb(uart_base);
}

void uart_put_char(unsigned char c)
{
    if (c == '\n') {
        outb(uart_base, '\r');
        outb(uart_base, '\n');
        return;
    }
    outb(uart_base, c);
}

void uart_put_chars(char* str)
{
	char *p;
    for (p = str; *p; ++p) {
        uart_put_char(*p);
    }
}
