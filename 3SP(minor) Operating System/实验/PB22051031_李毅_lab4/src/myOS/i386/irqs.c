#include "../include/vga.h"

void ignoreIntBody(void){
    put_chars("Unknown interrupt1\0",0x4,24,0);
}