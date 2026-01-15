#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__

/* 前向声明 */
struct myTCB;

/* 先进先出队列结构 */
typedef struct taskQueueFIFO {
    struct myTCB *head;
    struct myTCB *tail;
    int size;
} taskQueueFIFO;

/* 优先队列结构 */
typedef struct taskQueuePrio {
    struct myTCB **heap;
    int size;
    int capacity;
    int (*compare)(struct myTCB *a, struct myTCB *b);  /* 比较函数指针 */
} taskQueuePrio;

/* FIFO队列操作 */
void taskQueueFIFOInit(taskQueueFIFO *queue);
int taskQueueFIFOIsEmpty(taskQueueFIFO *queue);
void taskQueueFIFOEnqueue(taskQueueFIFO *queue, struct myTCB *task);
struct myTCB *taskQueueFIFODequeue(taskQueueFIFO *queue);
struct myTCB *taskQueueFIFOPeek(taskQueueFIFO *queue);
int taskQueueFIFOSize(taskQueueFIFO *queue);

/* 优先队列操作 */
void taskQueuePrioInit(taskQueuePrio *queue, int capacity, int (*compare)(struct myTCB *a, struct myTCB *b));
int taskQueuePrioIsEmpty(taskQueuePrio *queue);
void taskQueuePrioEnqueue(taskQueuePrio *queue, struct myTCB *task);
struct myTCB *taskQueuePrioDequeue(taskQueuePrio *queue);
struct myTCB *taskQueuePrioPeek(taskQueuePrio *queue);
int taskQueuePrioSize(taskQueuePrio *queue);

/* 比较函数 */
int compareBurstTime(struct myTCB *a, struct myTCB *b);    /* SJF用，比较执行时间 */
int comparePriority(struct myTCB *a, struct myTCB *b);     /* 优先级调度用 */
int compareArrivalTime(struct myTCB *a, struct myTCB *b);  /* 到达时间比较 */

#endif
