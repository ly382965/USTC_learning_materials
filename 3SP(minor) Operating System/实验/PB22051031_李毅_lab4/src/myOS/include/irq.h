#ifndef __IRQ_H__
#define __IRQ_H__

void disable_interrupt(void);   //although defined in i386/irq.S, it's a general interface used by OS kernel
void enable_interrupt(void);

#endif