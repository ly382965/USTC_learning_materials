#ifndef __WALLCLOCK_H__
#define __WALLCLOCK_H__

void getWallClock(int *h, int *m, int *s);
void setWallClock(int h, int m, int s);
void setWallClockHook(void (*func)(void));

#endif