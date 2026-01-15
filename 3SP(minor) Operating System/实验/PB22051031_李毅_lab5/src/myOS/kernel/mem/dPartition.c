#include "../../include/myPrintk.h"

struct dPartition{
	unsigned long size;
	unsigned long firstFreeStart; // for free list
};

void showdPartition(struct dPartition *dp){
	myPrintk(0x5,"dPartition(start=0x%x, size=0x%x, firstFreeStart=0x%x)\n", dp, dp->size,dp->firstFreeStart);
}

#define DP_MINIMUM_SIZE (sizeof(struct EMB)+sizeof(struct dPartition))

// for each memory block
struct EMB{
	unsigned long size;
	union {
		unsigned long nextStart;    // if free: pointer to next block
        unsigned long userData;		// if allocated, blongs to user
	};	                           
};

void showEMB(struct EMB * emb){
	myPrintk(0x3,"EMB(start=0x%x, size=0x%x, nextStart=0x%x)\n", emb, emb->size, emb->nextStart);
}

#define EMB_MINIMUM_SIZE sizeof(struct EMB)
#define EMB_OVERHEAD (sizeof(struct EMB)-sizeof(struct EMB*))  // overhead for EMB.size

unsigned long dPartitionInit(unsigned long start, unsigned long totalSize){
	struct dPartition * dpHeader;
	struct EMB *firstEMB;

	if (totalSize < DP_MINIMUM_SIZE) return 0;  //error size, too small

	dpHeader = (struct dPartition*)start;
	dpHeader->size  = totalSize;	
	dpHeader->firstFreeStart = (unsigned long)(dpHeader+1);  //TODO: align? gap?
	
	firstEMB = (struct EMB*)(dpHeader->firstFreeStart);
	firstEMB->size = totalSize-sizeof(struct dPartition);	//TODO: align? gap?
	firstEMB->nextStart = 0;	 // at first, only one big free EMB
	return start;  //as the handler
}

void dPartitionWalkByAddr(unsigned long dp){
	unsigned long emb = (unsigned long)(((struct dPartition*)dp)+1);
	unsigned long end = ((struct dPartition*)dp)->size + dp;

	showdPartition((struct dPartition *)dp);
	while(emb < end){
		showEMB((struct EMB*)emb);
		emb += ((struct EMB*)emb)->size;
	}
}

//=================firstfit, order: address, low-->high=====================
/**
 * return value: addr (without overhead, can directly used by user)
**/
unsigned long dPartitionAllocFirstFit(unsigned long dp, unsigned long size){
	struct dPartition *dpHeader;
	unsigned long toBeAlloc, prev=0, next, rear;
	unsigned long actualSize = size + EMB_OVERHEAD;
	unsigned long sizeLeft;
	int notfind=1;

	actualSize = ((actualSize+3)>>2)<<2;  //align to 4 bytes
	if (actualSize<EMB_MINIMUM_SIZE) actualSize = EMB_MINIMUM_SIZE;

	// find the first fit
	dpHeader = (struct dPartition*)dp;
	toBeAlloc = dpHeader->firstFreeStart;

	while (notfind) {
		if (toBeAlloc == 0) {
			notfind = 1;
			break;   // not find, &finish
		}

		if (actualSize <= ((struct EMB*)toBeAlloc)->size) {
			notfind=0;
			break;  // find, &finish
		}
		
		//next loop
		prev = toBeAlloc;
		toBeAlloc = ((struct EMB*)prev)->nextStart;
	}

	if(notfind) return 0;
	else {	//find, cut or not?
		
		next = ((struct EMB*)toBeAlloc)->nextStart;

		sizeLeft = ((struct EMB*)toBeAlloc)->size - actualSize;
		if (sizeLeft >= EMB_MINIMUM_SIZE) { 
			
			// cut
			rear = toBeAlloc + actualSize;
			((struct EMB*)rear)->size = sizeLeft;

			// insert rear
			((struct EMB*)rear)->nextStart = next;
			next = rear;

			// adjust toBeAlloc->size
			((struct EMB*)toBeAlloc)->size = actualSize;			
		}
		
		// link prev to next
		if(prev) ((struct EMB*)prev)->nextStart = next;
		else dpHeader->firstFreeStart = next;

		/*//fill with "0xA", just for test
		{
			char* p = (char*) (curr+OVERHEAD_EMB);  // calc overhead
			for(int i=0; i<actualSize-OVERHEAD_EMB;i++) *p++=0xAA;
		}*/
		return toBeAlloc+EMB_OVERHEAD;  //after EMB.size
	} 
}

/*
 *return value: 0:error; 1:OK
 */
unsigned long dPartitionFreeFirstFit(unsigned long dp, unsigned long start){
	unsigned long toBeFree = start - EMB_OVERHEAD;
	unsigned long prev=0, next, end;
	struct dPartition *dpHeader;
	int notfind=1;

	dpHeader = (struct dPartition*)dp;	

	end = toBeFree + ((struct EMB*)toBeFree)->size;
	
	//检查toBeFree~end是否在dp有效分配范围内
	if (toBeFree < (unsigned long)(dpHeader+1)) return 0;
	if (end > dp + dpHeader->size ) return 0;

	//find position in freelist, low...high
	next = dpHeader->firstFreeStart;
	prev = 0;
	while(notfind){		
		if ((next == 0)||(next > toBeFree)) { 
			notfind = 0;
			//myPrintk(0x4,"prev=0x%x, toBeFree=0x%x, end=0x%x, next=0x%x\n",prev, toBeFree, end, next);

			// link toBeFree to next
			if (end == next) { //合并
				((struct EMB*)toBeFree)->size += ((struct EMB*)next)->size;
				((struct EMB*)toBeFree)->nextStart = ((struct EMB*)next)->nextStart;
			} else {	//不合并
				// insert toBeFree before next
				((struct EMB*)toBeFree)->nextStart = next;
			}
			
			// link prev to toBeFree
			if (prev == 0) // the first?
				dpHeader->firstFreeStart = toBeFree;
			else if (toBeFree == prev + ((struct EMB*)prev)->size) {//合并
				((struct EMB*)prev)->size += ((struct EMB*)toBeFree)->size;					
				((struct EMB*)prev)->nextStart = ((struct EMB*)toBeFree)->nextStart;					
			} else //不合并
				((struct EMB*)prev)->nextStart = toBeFree;			
			
			break;
		}

		prev = next;
		next = ((struct EMB*)next)->nextStart;
	}

	/*//fill with "F", just for test
	{
		char* p = (char*)((unsigned long)curr+sizeof(struct EMB));  // calc overhead		
		for(int i=0; i<curr->size-sizeof(struct EMB);i++) *p++=0xFF;
	}*/
	return 1;
}

//wrap: we select firstFit, you can select another one
//user need not know this
unsigned long dPartitionAlloc(unsigned long dp, unsigned long size){
	return dPartitionAllocFirstFit(dp,size);
}

unsigned long dPartitionFree(unsigned long	 dp, unsigned long start){
	return dPartitionFreeFirstFit(dp,start);
}
