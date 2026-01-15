#include "../../include/mem.h"

unsigned long malloc(unsigned long size){
    return dPartitionAlloc(pMemHandler,size);
}

unsigned long free(unsigned long start){
    return dPartitionFree(pMemHandler,start);
}