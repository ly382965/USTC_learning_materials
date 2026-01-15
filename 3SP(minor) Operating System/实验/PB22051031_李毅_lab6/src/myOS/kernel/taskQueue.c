#include "../include/taskQueue.h"
#include "../include/task.h"
#include "../include/myPrintk.h"

#define NULL ((void *)0)
#define TASK_NUM (2 + USER_TASK_NUM)

/* FIFO队列操作实现 */
void taskQueueFIFOInit(taskQueueFIFO *queue) {
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

int taskQueueFIFOIsEmpty(taskQueueFIFO *queue) {
    return queue->head == NULL;
}

void taskQueueFIFOEnqueue(taskQueueFIFO *queue, struct myTCB *task) {
    task->nextTCB = NULL;
    
    if (taskQueueFIFOIsEmpty(queue)) {
        queue->head = task;
        queue->tail = task;
    } else {
        queue->tail->nextTCB = task;
        queue->tail = task;
    }
    queue->size++;
}

struct myTCB *taskQueueFIFODequeue(taskQueueFIFO *queue) {
    if (taskQueueFIFOIsEmpty(queue)) {
        return NULL;
    }
    
    struct myTCB *task = queue->head;
    queue->head = task->nextTCB;
    
    if (queue->head == NULL) {
        queue->tail = NULL;
    }
    
    task->nextTCB = NULL;
    queue->size--;
    return task;
}

struct myTCB *taskQueueFIFOPeek(taskQueueFIFO *queue) {
    return queue->head;
}

int taskQueueFIFOSize(taskQueueFIFO *queue) {
    return queue->size;
}

/* 优先队列操作实现 */
static struct myTCB *prioHeapArray[32];  /* 静态数组作为堆存储，使用固定大小 */

void taskQueuePrioInit(taskQueuePrio *queue, int capacity, int (*compare)(struct myTCB *a, struct myTCB *b)) {
    queue->heap = prioHeapArray;
    queue->size = 0;
    queue->capacity = capacity > 32 ? 32 : capacity;
    queue->compare = compare;
}

int taskQueuePrioIsEmpty(taskQueuePrio *queue) {
    return queue->size == 0;
}

/* 堆的上浮操作 */
static void heapifyUp(taskQueuePrio *queue, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (queue->compare(queue->heap[index], queue->heap[parent]) >= 0) {
            break;
        }
        
        /* 交换元素 */
        struct myTCB *temp = queue->heap[index];
        queue->heap[index] = queue->heap[parent];
        queue->heap[parent] = temp;
        
        index = parent;
    }
}

/* 堆的下沉操作 */
static void heapifyDown(taskQueuePrio *queue, int index) {
    while (1) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        
        if (left < queue->size && 
            queue->compare(queue->heap[left], queue->heap[smallest]) < 0) {
            smallest = left;
        }
        
        if (right < queue->size && 
            queue->compare(queue->heap[right], queue->heap[smallest]) < 0) {
            smallest = right;
        }
        
        if (smallest == index) {
            break;
        }
        
        /* 交换元素 */
        struct myTCB *temp = queue->heap[index];
        queue->heap[index] = queue->heap[smallest];
        queue->heap[smallest] = temp;
        
        index = smallest;
    }
}

void taskQueuePrioEnqueue(taskQueuePrio *queue, struct myTCB *task) {
    if (queue->size >= queue->capacity) {
        myPrintk(0x2, "Priority queue is full!\n");
        return;
    }
    
    queue->heap[queue->size] = task;
    heapifyUp(queue, queue->size);
    queue->size++;
}

struct myTCB *taskQueuePrioDequeue(taskQueuePrio *queue) {
    if (taskQueuePrioIsEmpty(queue)) {
        return NULL;
    }
    
    struct myTCB *task = queue->heap[0];
    queue->heap[0] = queue->heap[queue->size - 1];
    queue->size--;
    
    if (queue->size > 0) {
        heapifyDown(queue, 0);
    }
    
    return task;
}

struct myTCB *taskQueuePrioPeek(taskQueuePrio *queue) {
    if (taskQueuePrioIsEmpty(queue)) {
        return NULL;
    }
    return queue->heap[0];
}

int taskQueuePrioSize(taskQueuePrio *queue) {
    return queue->size;
}

/* 比较函数实现 */
int compareBurstTime(struct myTCB *a, struct myTCB *b) {
    unsigned long burstA = a->taskParam.burstTime;
    unsigned long burstB = b->taskParam.burstTime;
    
    if (burstA < burstB) return -1;
    if (burstA > burstB) return 1;
    return 0;
}

int comparePriority(struct myTCB *a, struct myTCB *b) {
    unsigned long prioA = a->taskParam.priority;
    unsigned long prioB = b->taskParam.priority;
    
    /* 优先级数值越小，优先级越高 */
    if (prioA < prioB) return -1;
    if (prioA > prioB) return 1;
    return 0;
}

int compareArrivalTime(struct myTCB *a, struct myTCB *b) {
    unsigned long arrivalA = a->taskParam.arrivalTime;
    unsigned long arrivalB = b->taskParam.arrivalTime;
    
    if (arrivalA < arrivalB) return -1;
    if (arrivalA > arrivalB) return 1;
    return 0;
}
