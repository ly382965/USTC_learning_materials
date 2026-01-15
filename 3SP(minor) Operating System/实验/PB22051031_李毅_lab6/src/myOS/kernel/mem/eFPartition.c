#include "../../include/myPrintk.h"
// for each empty block
struct EEB {
	unsigned long next_start;
};

void showEEB(struct EEB *eeb){
	myPrintk(0x7,"EEB(start=0x%x, next=0x%x)\n", eeb, eeb->next_start);
}

struct eFPartition{
	unsigned long totalN;
	unsigned long perSize;  //unit: byte	
	unsigned long firstFree;
};

void showeFPartition(struct eFPartition *efp){
	myPrintk(0x5,"eFPartition(start=0x%x, totalN=0x%x, perSize=0x%x, firstFree=0x%x)\n", efp, efp->totalN, efp->perSize, efp->firstFree);
}

void eFPartitionWalkByAddr(unsigned long efpHandler){
	int i;
	struct eFPartition * efp = (struct eFPartition*)efpHandler;
	struct EEB * eeb = (struct EEB*)(efp+1);

	showeFPartition(efp);
	for (i=0;i<efp->totalN;i++){
		showEEB(eeb);
		eeb = (struct EEB*)((unsigned long)eeb + efp->perSize);
	}
}

#define OVERHEAD_EFP (sizeof(struct eFPartition))
unsigned long eFPartitionTotalSize(unsigned long perSize, unsigned long n){
	unsigned actualSize = ((perSize + 3) >> 2) << 2;   // aligned up to 4
	return (actualSize*n+OVERHEAD_EFP);
}

unsigned long eFPartitionInit(unsigned long start, unsigned long perSize, unsigned long n){
	struct EEB * nextEEB;
	unsigned long nextStart = start + OVERHEAD_EFP;
	unsigned long actualSize = ((perSize + 3) >> 2) << 2;   // aligned up to 4
	struct eFPartition * theEFP = (struct eFPartition*)start;

	theEFP->totalN    = n;
	theEFP->perSize   = actualSize;
	theEFP->firstFree = nextStart;

	for(int i=0; i<n ; i++) {
		nextEEB = (struct EEB *)nextStart;
		nextStart += actualSize;
		nextEEB->next_start = nextStart;

		/*{ //only for test: the empty block is padded with "0xEEEEEEEE"
			unsigned long *nextSignature = (unsigned long*)(nextStart+sizeof(unsigned long));
			for(int j=1; j< (actualSize>>2); j++) {
				*nextSignature = 0xEEEEEEEE;
				nextSignature ++;	
			}
		}*/
	}

	nextEEB->next_start = 0;
	return start;
}

/*
 * return value: 0=failed; other=the start of the memory block
 */
unsigned long eFPartitionAlloc(unsigned long EFPHandler){
	struct eFPartition * theEFP = (struct eFPartition*)EFPHandler;
	unsigned long addr = theEFP->firstFree;
	if (addr!=0)
		theEFP->firstFree = ((struct EEB*)(addr))->next_start;

  /*{ //only for test: the allocated block is padded with "0xEAEAEAEA"
		unsigned long *nextSignature = (unsigned long*)addr;
		unsigned long actualSize = ((theEFP->perSize + 3) >> 2) << 2;   // aligned up to 4
		for(int j=0; j< (actualSize>>2); j++) {
			*nextSignature = 0xEAEAEAEA;
			nextSignature ++;	
		}
	}*/

	return addr;
}

/*
 *return value: 0=error; 1=ok
 */
unsigned long eFPartitionFree(unsigned long EFPHandler,unsigned long mbStart){
	struct eFPartition * theEFP;
  struct EEB* newFree;

	theEFP = (struct eFPartition*)EFPHandler;
	
	//TODO: check if mbstart is in the EFP

	newFree = (struct EEB*)mbStart;
	newFree->next_start = theEFP->firstFree;
	theEFP->firstFree = mbStart;

	/*{ //only for test: the empty block is padded with "0xFFFFFFFF"
		unsigned long *nextSignature = (unsigned long*)(mbStart+sizeof(unsigned long));
		unsigned long actualSize = ((theEFP->perSize + 3) >> 2) << 2;   // aligned up to 4
		for(int j=1; j< (actualSize>>2); j++) {
			*nextSignature = 0xFFFFFFFF;
			nextSignature ++;	
		}
	}*/
	return 1;
}
