#include "wallClock.h"
int system_ticks;
int HH,MM,SS;
//NOTE:你可以自行定义接口来辅助实现

void tick(void){
	system_ticks++;
	//TODO 你需要填写它，100个时钟周期增加1秒
	if (system_ticks % 100 == 0) 
	{
        SS++;
        if (SS >= 60) 
		{
            SS = 0;
            MM++;
            if (MM >= 60) 
			{
                MM = 0;
                HH = (HH + 1) % 24;
            }
        }
    }
	setWallClock(HH,MM,SS);
	return;
}

