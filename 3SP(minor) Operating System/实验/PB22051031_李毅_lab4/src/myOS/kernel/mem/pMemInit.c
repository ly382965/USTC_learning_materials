#include "../../include/myPrintk.h"
#include "../../include/mem.h"
unsigned long pMemStart;  // 可用的内存的起始地址
unsigned long pMemSize;  // 可用的大小

unsigned long pMemHandler;  // 用户动态区的句柄
unsigned long kMemHandler;  // 内核动态区的句柄

void memTest(unsigned long start, unsigned long grainSize){
	// TODO
	/*功能：检测算法
		这一个函数对应实验讲解ppt中的第一大功能-内存检测。
		本函数的功能是检测从start开始有多大的内存可用，具体算法参照ppt检测算法的文字描述
	注意点三个：
	1、覆盖写入和读出就是往指针指向的位置写和读，不要想复杂。
	  (至于为什么这种检测内存的方法可行大家要自己想一下)
	2、开始的地址要大于1M，需要做一个if判断。
	3、grainsize不能太小，也要做一个if判断
	*/
	/*
	从start开始，以grainSize为步长，进行内存检测
	检测方法：
	1读出grain的头2个字节
	2）覆盖写入0xAA55，再读出并检查是否是0xAA55，若不是则检测结束；
	3）覆盖写入0x55AA，再读出并检查是否是0x55AA，若不是则检测结束；
	4）写回原来的值
	5）对grain的尾2个字节，重复2-4
	6）步进到下一个grain，重复1-5，直到检测结束
	*/
    if (start < 0x100000 || grainSize < sizeof(unsigned short)) 
	{
        pMemStart = pMemSize = 0;
        myPrintk(0x7, "MemStart: %x  \n", pMemStart);
        myPrintk(0x7, "MemSize:  %x  \n", pMemSize);
        return;
    }

    unsigned long addr = start;
    unsigned long size = 0;

    while (1) 
	{
        // 检测 head 两字节
        unsigned short *head = (unsigned short *)addr;
        unsigned short oldHead = *head;
        *head = 0xAA55;
        if (*head != 0xAA55) break;
        *head = 0x55AA;
        if (*head != 0x55AA) break;
        *head = oldHead;

        // 检测 tail 两字节
        unsigned short *tail = (unsigned short *)(addr + grainSize - sizeof(unsigned short));
        unsigned short oldTail = *tail;
        *tail = 0xAA55;
        if (*tail != 0xAA55) break;
        *tail = 0x55AA;
        if (*tail != 0x55AA) break;
        *tail = oldTail;

        // 下一个 grain
        size += grainSize;
        addr += grainSize;
    }

    pMemStart = start;
    pMemSize  = size;
    myPrintk(0x7, "MemStart: %x  \n", pMemStart);
    myPrintk(0x7, "MemSize:  %x  \n", pMemSize);
}

extern unsigned long _end;
void pMemInit(void){
	unsigned long _end_addr = (unsigned long) &_end;
	memTest(0x100000,0x1000);
	myPrintk(0x7,"_end:  %x  \n", _end_addr);
	if (pMemStart <= _end_addr) {
		pMemSize -= _end_addr - pMemStart;
		pMemStart = _end_addr;
	}
	
	// TODO:此处选择不同的内存管理算法
	pMemHandler = dPartitionInit(pMemStart,pMemSize);
}
