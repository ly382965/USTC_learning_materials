#ifndef __SCHEDULERS_H__
#define __SCHEDULERS_H__

#include "schedTypes.h"
#include "taskQueue.h"

/* 前向声明 */
struct myTCB;

/* FCFS调度器 */
typedef struct schedulerFCFS {
    taskQueueFIFO readyQueue;
} schedulerFCFS;

/* SJF调度器 */
typedef struct schedulerSJF {
    taskQueuePrio readyQueue;
} schedulerSJF;

/* 优先级调度器 */
typedef struct schedulerPrio {
    taskQueuePrio readyQueue;
} schedulerPrio;

/* RR调度器 */
typedef struct schedulerRR {
    taskQueueFIFO readyQueue;
    unsigned long timeQuantum;     /* 时间片大小 */
    unsigned long currentQuantum;  /* 当前任务已用时间片 */
} schedulerRR;

/* FCFS调度器操作 */
void schedulerFCFSInit(schedulerFCFS *sched);
void schedulerFCFSAddTask(schedulerFCFS *sched, struct myTCB *task);
struct myTCB *schedulerFCFSGetNext(schedulerFCFS *sched);
int schedulerFCFSIsEmpty(schedulerFCFS *sched);

/* SJF调度器操作 */
void schedulerSJFInit(schedulerSJF *sched);
void schedulerSJFAddTask(schedulerSJF *sched, struct myTCB *task);
struct myTCB *schedulerSJFGetNext(schedulerSJF *sched);
int schedulerSJFIsEmpty(schedulerSJF *sched);

/* 优先级调度器操作 */
void schedulerPrioInit(schedulerPrio *sched);
void schedulerPrioAddTask(schedulerPrio *sched, struct myTCB *task);
struct myTCB *schedulerPrioGetNext(schedulerPrio *sched);
int schedulerPrioIsEmpty(schedulerPrio *sched);

/* RR调度器操作 */
void schedulerRRInit(schedulerRR *sched, unsigned long quantum);
void schedulerRRAddTask(schedulerRR *sched, struct myTCB *task);
struct myTCB *schedulerRRGetNext(schedulerRR *sched);
int schedulerRRIsEmpty(schedulerRR *sched);
void schedulerRRTick(schedulerRR *sched);  /* 时钟中断处理 */
int schedulerRRNeedPreempt(schedulerRR *sched);  /* 是否需要抢占 */

#endif
