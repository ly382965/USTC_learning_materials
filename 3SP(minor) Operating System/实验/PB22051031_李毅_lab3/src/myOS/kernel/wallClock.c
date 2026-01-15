#include "vga.h"
#include "wallClock.h"

//NOTE:实现了时钟设置和获取的接口，如何在tick函数中使用它们，随着时钟中断更新墙钟？
void setWallClock(int HH,int MM,int SS){
	//TODO 你需要填写它
	char time[8];//HH:MM:SS
	time[0] = HH / 10 + '0';
	time[1] = HH % 10 + '0';
	time[2] = ':';
	time[3] = MM / 10 + '0';
	time[4] = MM % 10 + '0';
	time[5] = ':';
	time[6] = SS / 10 + '0';
	time[7] = SS % 10 + '0';

	put_chars(time, 0x3, VGA_ROW - 1, VGA_COL - 8);
}

void getWallClock(int *h, int *m, int *s){
	//TODO 你需要填写它
    extern int HH, MM, SS;  // 声明在 tick.c 中定义的全局变量
    *h = HH;
    *m = MM;
    *s = SS;
}