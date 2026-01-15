#ifndef __TICK_H__
#define __TICK_H__
#include "wallClock.h"
extern int system_ticks;
extern int HH,MM,SS;

void enable_interrupt(void);
void disable_interrupt(void);
void tick(void);

#endif
