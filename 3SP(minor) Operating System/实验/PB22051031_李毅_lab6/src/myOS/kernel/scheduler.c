#include "../include/scheduler.h"
#include "../include/schedulers.h"
#include "../include/taskArrv.h"
#include "../include/task.h"

#define NULL ((void *)0)

void schedulerInit(scheduler *sched, schedType type, unsigned long timeQuantum) {
    sched->type = type;
    
    switch (type) {
        case SCHED_FCFS:
            schedulerFCFSInit(&(sched->impl.fcfs));
            break;
        case SCHED_SJF:
            schedulerSJFInit(&(sched->impl.sjf));
            break;
        case SCHED_PRIO:
            schedulerPrioInit(&(sched->impl.prio));
            break;
        case SCHED_RR:
            schedulerRRInit(&(sched->impl.rr), timeQuantum);
            break;
    }
    
    taskArrvInit(&(sched->arrvManager));
    sched->idleTask = NULL;
}

void schedulerAddTask(scheduler *sched, myTCB *task) {
    /* 如果任务有到达时间，先加入到达管理器 */
    if (task->taskParam.arrivalTime > systemTick) {
        taskArrvAddTask(&(sched->arrvManager), task);
        return;
    }
    
    /* 否则直接加入就绪队列 */
    switch (sched->type) {
        case SCHED_FCFS:
            schedulerFCFSAddTask(&(sched->impl.fcfs), task);
            break;
        case SCHED_SJF:
            schedulerSJFAddTask(&(sched->impl.sjf), task);
            break;
        case SCHED_PRIO:
            schedulerPrioAddTask(&(sched->impl.prio), task);
            break;
        case SCHED_RR:
            schedulerRRAddTask(&(sched->impl.rr), task);
            break;
    }
}

myTCB *schedulerGetNextTask(scheduler *sched) {
    myTCB *nextTask = NULL;
    
    /* 首先检查是否有新到达的任务 */
    taskArrvUpdate(&(sched->arrvManager));
    while (taskArrvHasArrived(&(sched->arrvManager))) {
        myTCB *arrivedTask = taskArrvGetNext(&(sched->arrvManager));
        schedulerAddTask(sched, arrivedTask);
    }
    
    /* 从相应的调度器获取下一个任务 */
    switch (sched->type) {
        case SCHED_FCFS:
            nextTask = schedulerFCFSGetNext(&(sched->impl.fcfs));
            break;
        case SCHED_SJF:
            nextTask = schedulerSJFGetNext(&(sched->impl.sjf));
            break;
        case SCHED_PRIO:
            nextTask = schedulerPrioGetNext(&(sched->impl.prio));
            break;
        case SCHED_RR:
            nextTask = schedulerRRGetNext(&(sched->impl.rr));
            break;
    }
    
    /* 如果没有就绪任务，返回idle任务 */
    if (nextTask == NULL) {
        nextTask = sched->idleTask;
    }
    
    return nextTask;
}

void schedulerTick(scheduler *sched) {
    systemTick++;
    
    if (sched->type == SCHED_RR) {
        schedulerRRTick(&(sched->impl.rr));
    }
}

int schedulerNeedPreempt(scheduler *sched) {
    if (sched->type == SCHED_RR) {
        return schedulerRRNeedPreempt(&(sched->impl.rr));
    }
    return 0;  /* 其他调度算法不支持抢占 */
}

void schedulerSetIdleTask(scheduler *sched, myTCB *idleTask) {
    sched->idleTask = idleTask;
}

void schedulerTaskComplete(scheduler *sched, myTCB *task) {
    /* 任务完成时的清理工作 */
    task->taskParam.endTime = systemTick;
    /* 这里可以添加更多的任务完成处理逻辑 */
}
