#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "schedTypes.h"
#include "schedulers.h"
#include "taskArrv.h"

/* 前向声明 */
struct myTCB;

/* 统一调度器接口 */
typedef struct scheduler {
    schedType type;
    union {
        schedulerFCFS fcfs;
        schedulerSJF sjf;
        schedulerPrio prio;
        schedulerRR rr;
    } impl;
    
    taskArrvManager arrvManager;  /* 任务到达管理器 */
    struct myTCB *idleTask;             /* idle任务 */
} scheduler;

/* 调度器接口操作 */
void schedulerInit(scheduler *sched, schedType type, unsigned long timeQuantum);
void schedulerAddTask(scheduler *sched, struct myTCB *task);
struct myTCB *schedulerGetNextTask(scheduler *sched);
void schedulerTick(scheduler *sched);  /* 系统时钟中断处理 */
int schedulerNeedPreempt(scheduler *sched);  /* 是否需要抢占 */
void schedulerSetIdleTask(scheduler *sched, struct myTCB *idleTask);

/* 任务完成时的处理 */
void schedulerTaskComplete(scheduler *sched, struct myTCB *task);

#endif
