#include "../include/io.h"

#define uart_base 0x3F8

void uart_put_char(unsigned char c){
    outb(uart_base,c);
}

unsigned char uart_get_char(void){
    while (!(inb(uart_base+5)&1));
    
    return inb(uart_base);                
}

void uart_put_chars(char *str){ 
    char c, *current = str ;        
    while(c = *current++) {
        if (c =='\n') uart_put_char('\r');      
        uart_put_char(c);
    }
}