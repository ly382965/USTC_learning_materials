#include "../include/schedulers.h"
#include "../include/taskQueue.h"
#include "../include/task.h"

/* FCFS调度器实现 */
void schedulerFCFSInit(schedulerFCFS *sched) {
    taskQueueFIFOInit(&(sched->readyQueue));
}

void schedulerFCFSAddTask(schedulerFCFS *sched, myTCB *task) {
    taskQueueFIFOEnqueue(&(sched->readyQueue), task);
}

myTCB *schedulerFCFSGetNext(schedulerFCFS *sched) {
    return taskQueueFIFODequeue(&(sched->readyQueue));
}

int schedulerFCFSIsEmpty(schedulerFCFS *sched) {
    return taskQueueFIFOIsEmpty(&(sched->readyQueue));
}

/* SJF调度器实现 */
void schedulerSJFInit(schedulerSJF *sched) {
    taskQueuePrioInit(&(sched->readyQueue), TASK_NUM, compareBurstTime);
}

void schedulerSJFAddTask(schedulerSJF *sched, myTCB *task) {
    taskQueuePrioEnqueue(&(sched->readyQueue), task);
}

myTCB *schedulerSJFGetNext(schedulerSJF *sched) {
    return taskQueuePrioDequeue(&(sched->readyQueue));
}

int schedulerSJFIsEmpty(schedulerSJF *sched) {
    return taskQueuePrioIsEmpty(&(sched->readyQueue));
}

/* 优先级调度器实现 */
void schedulerPrioInit(schedulerPrio *sched) {
    taskQueuePrioInit(&(sched->readyQueue), TASK_NUM, comparePriority);
}

void schedulerPrioAddTask(schedulerPrio *sched, myTCB *task) {
    taskQueuePrioEnqueue(&(sched->readyQueue), task);
}

myTCB *schedulerPrioGetNext(schedulerPrio *sched) {
    return taskQueuePrioDequeue(&(sched->readyQueue));
}

int schedulerPrioIsEmpty(schedulerPrio *sched) {
    return taskQueuePrioIsEmpty(&(sched->readyQueue));
}

/* RR调度器实现 */
void schedulerRRInit(schedulerRR *sched, unsigned long quantum) {
    taskQueueFIFOInit(&(sched->readyQueue));
    sched->timeQuantum = quantum;
    sched->currentQuantum = 0;
}

void schedulerRRAddTask(schedulerRR *sched, myTCB *task) {
    taskQueueFIFOEnqueue(&(sched->readyQueue), task);
}

myTCB *schedulerRRGetNext(schedulerRR *sched) {
    sched->currentQuantum = 0;  /* 重置时间片计数 */
    return taskQueueFIFODequeue(&(sched->readyQueue));
}

int schedulerRRIsEmpty(schedulerRR *sched) {
    return taskQueueFIFOIsEmpty(&(sched->readyQueue));
}

void schedulerRRTick(schedulerRR *sched) {
    sched->currentQuantum++;
}

int schedulerRRNeedPreempt(schedulerRR *sched) {
    return (sched->currentQuantum >= sched->timeQuantum) && 
           (!taskQueueFIFOIsEmpty(&(sched->readyQueue)));
}
