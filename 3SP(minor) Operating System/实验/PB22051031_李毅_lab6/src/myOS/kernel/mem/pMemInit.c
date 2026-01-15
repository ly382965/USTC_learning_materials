#include "../../include/myPrintk.h"
#include "../../include/mem.h"
unsigned long pMemStart;
unsigned long pMemSize;

void memTest(unsigned long start, unsigned long grainSize){
	int notFinished = 1;
	unsigned short *toTestAddr;
	unsigned short temp;

	if (start<0x100000) {
		myPrintk(0x7,"????????  IN memTest: start is too small, sould>=1MB  ????????\n"); while(1);
	}

	if (grainSize<0x1000) {
		myPrintk(0x7,"????????  IN memTest: grainSize is too small, should>=4KB  ????????\n"); while(1);
	}

	pMemStart = start;
	toTestAddr = (unsigned short*) start;
	while(notFinished){
		temp= *toTestAddr;
		
		*toTestAddr = 0xAA55;
		if(*toTestAddr!=0xAA55) {
			notFinished=0;
			break;
		}

		*toTestAddr = 0x55AA;
		if(*toTestAddr!=0x55AA) {
			notFinished=0;
			break;
		}

		*toTestAddr = temp;

		toTestAddr += grainSize/sizeof(unsigned short);
	}
	
	pMemSize = (unsigned long)toTestAddr - start;

	myPrintk(0x7,"MemStart: %x  \n",pMemStart);
	myPrintk(0x7,"MemSize:  %x  \n",pMemSize);
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

	pMemHandler = dPartitionInit(pMemStart,pMemSize);	
}
