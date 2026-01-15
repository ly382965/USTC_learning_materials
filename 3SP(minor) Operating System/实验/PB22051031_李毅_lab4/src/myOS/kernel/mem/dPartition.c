#include "../../include/myPrintk.h"


//dPartition 是整个动态分区内存的数据结构
typedef struct dPartition{
	unsigned long size;
	unsigned long firstFreeStart; 
} dPartition;	//共占8个字节

#define dPartition_size ((unsigned long)0x8)

void showdPartition(struct dPartition *dp){
	myPrintk(0x5,"dPartition(start=0x%x, size=0x%x, firstFreeStart=0x%x)\n", dp, dp->size,dp->firstFreeStart);
}

// EMB 是每一个block的数据结构，userdata可以暂时不用管。
typedef struct EMB{
	unsigned long size;
	union {
		unsigned long nextStart;    // if free: pointer to next block
        unsigned long userData;		// if allocated, belongs to user
	};	                           
} EMB;	//共占8个字节

#define EMB_size ((unsigned long)0x8)

void showEMB(struct EMB * emb){
	myPrintk(0x3,"EMB(start=0x%x, size=0x%x, nextStart=0x%x)\n", emb, emb->size, emb->nextStart);
}

#define ALIGN8(x)  ( ((x) + 7UL) & ~7UL ) //对齐到8字节

unsigned long dPartitionInit(unsigned long start, unsigned long totalSize)
{
	/*功能：初始化内存。
	1. 在地址start处，首先是要有dPartition结构体表示整个数据结构(也即句柄)。
	2. 然后，一整块的EMB被分配（以后使用内存会逐渐拆分），在内存中紧紧跟在dP后面，然后dP的firstFreeStart指向EMB。
	3. 返回start首地址(也即句柄)。
	注意有两个地方的大小问题：
	第一个是由于内存肯定要有一个EMB和一个dPartition，totalSize肯定要比这两个加起来大。
	第二个注意EMB的size属性不是totalsize，因为dPartition和EMB自身都需要要占空间。
	*/
    totalSize = ALIGN8(totalSize);

	// 检查总大小是否符合要求
    if (totalSize < dPartition_size + EMB_size) 
	{
        return 0;
    }

    struct dPartition *dp = (struct dPartition *)start;
    dp->size = totalSize;

    unsigned long embAddr = start + dPartition_size;
    struct EMB *emb = (struct EMB *)embAddr;

    emb->size = ALIGN8(totalSize - dPartition_size - EMB_size);
    emb->nextStart = 0;

    dp->firstFreeStart = embAddr;

    return start;
}


void dPartitionWalkByAddr(unsigned long dp){
	/*功能：本函数遍历输出EMB 方便调试
	1. 先打印dP的信息，可调用上面的showdPartition。
	2. 然后按地址的大小遍历EMB，对于每一个EMB，可以调用上面的showEMB输出其信息

	*/
	struct dPartition *pdp = (struct dPartition *)dp;
	unsigned long curr;
		
	showdPartition(pdp);

	curr = pdp->firstFreeStart;
	while (curr) 
	{
		showEMB((struct EMB *)curr);
		curr = ((struct EMB *)curr)->nextStart;
	}
}


//=================firstfit, order: address, low-->high=====================
/**
 * return value: addr (without overhead, can directly used by user)
**/

unsigned long dPartitionAllocFirstFit(unsigned long dp, unsigned long size)
{
	/*功能：分配一个空间
	1. 使用firstfit的算法分配空间，
	2. 成功分配返回首地址，不成功返回0
	3. 从空闲内存块组成的链表中拿出一块供我们来分配空间(如果提供给分配空间的内存块空间大于size，我们还将把剩余部分放回链表中)，并维护相应的空闲链表以及句柄
	注意的地方：
		1.EMB类型的数据的存在本身就占用了一定的空间。

	*/
	// 对齐
	size = ALIGN8(size);
	struct dPartition *pdp = (struct dPartition *)dp;
	unsigned long prev = 0;
	unsigned long curr = pdp->firstFreeStart;

	while (curr) 
	{
		struct EMB *pemb = (struct EMB *)curr;
		if (pemb->size >= size) 
		{
			// 实际可用内存的起始地址
			unsigned long userAddr = curr + EMB_size;
			// 空闲块剩余的大小
			unsigned long remain = pemb->size - size;

			// 如果剩余空间足够放下一个新的EMB块头，则进行分割
			if (remain > EMB_size) 
			{
				// 新建一个EMB
				unsigned long next = pemb->nextStart;
				unsigned long splitAddr = curr + EMB_size + size;
				struct EMB *newEmb = (struct EMB *)splitAddr;
				newEmb->size = ALIGN8(remain - EMB_size);
				newEmb->nextStart = next;

				// 将前一个空闲块的next设置为新的空闲块地址
				if (prev)
					((struct EMB *)prev)->nextStart = splitAddr;
				else
					pdp->firstFreeStart = splitAddr;

				// 更新当前块大小为请求大小
				pemb->size = size;
			} 
			else 
			{
				// 剩余空间不足以存放一个新的EMB，整体分配此块
				if (prev)
					((struct EMB *)prev)->nextStart = pemb->nextStart;
				else
					pdp->firstFreeStart = pemb->nextStart;
			}

			return userAddr;
		}
		prev = curr;
		curr = pemb->nextStart;
	}
	return 0;
}


unsigned long dPartitionFreeFirstFit(unsigned long dp, unsigned long start){
	/*功能：释放一个空间
	1. 按照对应的fit的算法释放空间
	2. 注意检查要释放的start~end这个范围是否在dp有效分配范围内
		返回1 没问题
		返回0 error
	3. 需要考虑两个空闲且相邻的内存块的合并
	
	*/
	struct dPartition *pdp = (struct dPartition *)dp;
	if (!start) return 0;
	// EMB 头部地址
	unsigned long embAddr = start - EMB_size;
	// 分区范围
	unsigned long partStart = dp;
	unsigned long partEnd   = dp + pdp->size;
	// 检查dp是否在有效分配范围内
	if (embAddr < partStart + dPartition_size || embAddr + EMB_size + ((struct EMB *)embAddr)->size > partEnd)
		return 0;

	struct EMB *freed = (struct EMB *)embAddr;
	unsigned long prev = 0;
	unsigned long curr = pdp->firstFreeStart;

	// 找到插入位置
	while (curr && curr < embAddr) 
	{
		prev = curr;
		curr = ((struct EMB *)curr)->nextStart;
	}
	// 将 freed 插入
	freed->nextStart = curr;
	if (prev)
		((struct EMB *)prev)->nextStart = embAddr;
	else
		pdp->firstFreeStart = embAddr;

	// 与后续块合并
	if (curr) 
	{
		unsigned long freedEnd = embAddr + EMB_size + freed->size;
		if (freedEnd == curr) 
		{
			freed->size += EMB_size + ((struct EMB *)curr)->size;
			freed->nextStart = ((struct EMB *)curr)->nextStart;
			curr = freed->nextStart;
		}
	}

	// 与前驱块合并
	if (prev) 
	{
		unsigned long prevEnd = prev + EMB_size + ((struct EMB *)prev)->size;
		if (prevEnd == embAddr) 
		{
			((struct EMB *)prev)->size += EMB_size + freed->size;
			((struct EMB *)prev)->nextStart = freed->nextStart;
		}
	}

	return 1;
	
}


// 进行封装，此处默认firstfit分配算法，当然也可以使用其他fit，不限制。
unsigned long dPartitionAlloc(unsigned long dp, unsigned long size){
	return dPartitionAllocFirstFit(dp,size);
}

unsigned long dPartitionFree(unsigned long	 dp, unsigned long start){
	return dPartitionFreeFirstFit(dp,start);
}
