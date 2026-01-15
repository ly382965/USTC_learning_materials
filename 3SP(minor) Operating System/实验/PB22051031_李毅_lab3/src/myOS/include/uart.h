#ifndef __UART_H__
#define __UART_H__

#define uart_base 0x3F8
#include "io.h"
unsigned char uart_get_char(void);
void uart_put_char(unsigned char c);
void uart_put_chars(char* str);

#endif
