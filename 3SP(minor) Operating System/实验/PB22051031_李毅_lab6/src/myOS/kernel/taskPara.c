#include "../include/taskPara.h"

/* 初始化任务参数 */
void taskParaInit(taskPara *para, unsigned long arrivalTime, 
                  unsigned long burstTime, unsigned long priority) {
    para->arrivalTime = arrivalTime;
    para->burstTime = burstTime;
    para->remainingTime = burstTime;
    para->priority = priority;
    para->startTime = 0;
    para->endTime = 0;
    para->waitTime = 0;
}

/* 设置任务参数 */
void setTaskArrivalTime(taskPara *para, unsigned long arrivalTime) {
    para->arrivalTime = arrivalTime;
}

void setTaskBurstTime(taskPara *para, unsigned long burstTime) {
    para->burstTime = burstTime;
    para->remainingTime = burstTime;
}

void setTaskPriority(taskPara *para, unsigned long priority) {
    para->priority = priority;
}

/* 获取任务参数 */
unsigned long getTaskArrivalTime(taskPara *para) {
    return para->arrivalTime;
}

unsigned long getTaskBurstTime(taskPara *para) {
    return para->burstTime;
}

unsigned long getTaskRemainingTime(taskPara *para) {
    return para->remainingTime;
}

unsigned long getTaskPriority(taskPara *para) {
    return para->priority;
}
