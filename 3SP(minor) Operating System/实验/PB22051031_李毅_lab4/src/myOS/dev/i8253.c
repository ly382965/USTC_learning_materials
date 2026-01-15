#include "../include/io.h"

void init8253(void){
    outb(0x43, 0x34);
    //~100HZ
    outb(0x40,11932 & 0xff);
    outb(0x40,11932 >>8);
    outb(0x21, inb(0x21) & 0xFE);
}