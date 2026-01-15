#ifndef __KMALLOC_H__
#define __KMALLOC_H__

#include "mem.h"

//for kernel
#define kmalloc(size)   dPartitionAlloc(pMemHandler,size)
#define kfree(start)	dPartitionFree(pMemHandler,start)

#endif