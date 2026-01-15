#include "io.h"

void init8253(void){
	//TODO 你需要填写它
	int f_8253 = 1193180; // 8253的时钟频率
	int f_time_interrupt = 100; // 定时中断频率
	unsigned short f_div = f_8253 / f_time_interrupt;

    outb(0x43, 0x34);
    outb(0x40, (unsigned char)f_div);
    outb(0x40, (unsigned char)(f_div >> 8));
}
