#ifndef __TASK_ARRV_H__
#define __TASK_ARRV_H__

#include "taskQueue.h"

/* 前向声明 */
struct myTCB;

extern unsigned long systemTick;  /* 系统时钟计数 */

/* 任务到达管理器 */
typedef struct taskArrvManager {
    taskQueuePrio waitingQueue;   /* 等待到达的任务队列，按到达时间排序 */
    taskQueueFIFO arrivedQueue;   /* 已到达的任务队列 */
} taskArrvManager;

/* 任务到达模块操作 */
void taskArrvInit(taskArrvManager *manager);
void taskArrvAddTask(taskArrvManager *manager, struct myTCB *task);
void taskArrvUpdate(taskArrvManager *manager);  /* 根据系统时钟更新到达的任务 */
struct myTCB *taskArrvGetNext(taskArrvManager *manager);  /* 获取下一个已到达的任务 */
int taskArrvHasArrived(taskArrvManager *manager);  /* 是否有已到达的任务 */

#endif
