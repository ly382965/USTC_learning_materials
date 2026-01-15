#ifndef __TASK_PARA_H__
#define __TASK_PARA_H__

typedef struct taskPara {
    unsigned long arrivalTime;    /* 任务到达时间 */
    unsigned long burstTime;      /* 任务执行时间(用于SJF) */
    unsigned long remainingTime;  /* 剩余执行时间 */
    unsigned long priority;       /* 任务优先级 */
    unsigned long startTime;      /* 任务开始时间 */
    unsigned long endTime;        /* 任务结束时间 */
    unsigned long waitTime;       /* 任务等待时间 */
} taskPara;

/* 初始化任务参数 */
void taskParaInit(taskPara *para, unsigned long arrivalTime, 
                  unsigned long burstTime, unsigned long priority);

/* 设置任务参数 */
void setTaskArrivalTime(taskPara *para, unsigned long arrivalTime);
void setTaskBurstTime(taskPara *para, unsigned long burstTime);
void setTaskPriority(taskPara *para, unsigned long priority);

/* 获取任务参数 */
unsigned long getTaskArrivalTime(taskPara *para);
unsigned long getTaskBurstTime(taskPara *para);
unsigned long getTaskRemainingTime(taskPara *para);
unsigned long getTaskPriority(taskPara *para);

#endif
