#ifndef __TASK_H__
#define __TASK_H__

#ifndef USER_TASK_NUM
#include "../../userApp/userApp.h"
#endif

#include "taskPara.h"
#include "schedTypes.h"

#define TASK_NUM (2 + USER_TASK_NUM)   // at least: 0-idle, 1-init

#define initTskBody myMain         // connect initTask with myMain

#define STACK_SIZE 512            // definition of STACK_SIZE

void initTskBody(void);

void CTX_SW(void*prev_stkTop, void*next_stkTop);

//#error "TODO: 为 myTCB 增补合适的字段"
typedef struct myTCB {
     unsigned long *stkTop;        /* 栈顶指针 */
     unsigned long stack[STACK_SIZE];      /* 开辟了一个大小为STACK_SIZE的栈空间 */  
     unsigned long TSK_State;   /* 进程状态 */
     unsigned long TSK_ID;      /* 进程ID */ 
     void (*task_entrance)(void);  /*进程的入口地址*/
     struct myTCB * nextTCB;           /*下一个TCB*/
     taskPara taskParam;              /* 任务参数 */
} myTCB;


extern myTCB tcbPool[TASK_NUM];//进程池的大小设置

extern myTCB* idleTsk;                /* idle 任务 */
extern myTCB* currentTsk;             /* 当前任务 */
extern myTCB* firstFreeTsk;           /* 下一个空闲的 TCB */

extern schedType currentSchedType;

/* 新增调度器相关接口 */
int createTskWithParam(void (*tskBody)(void), unsigned long arrivalTime, 
                      unsigned long burstTime, unsigned long priority);
void schedule(void);  /* 调度函数 */
void schedulerTimerHandler(void);  /* 时钟中断处理 */

/* 调度算法切换接口 */
void setSchedulingAlgorithm(schedType type, unsigned long timeQuantum);
schedType getCurrentSchedulingAlgorithm(void);
int createTestTask(void (*taskBody)(void), const char* name, 
                   unsigned long arrivalTime, unsigned long burstTime, 
                   unsigned long priority);

void TaskManagerInit(void);

#endif
