#include "../include/taskArrv.h"
#include "../include/taskPara.h"
#include "../include/task.h"

unsigned long systemTick = 0;  /* 系统时钟计数 */

void taskArrvInit(taskArrvManager *manager) {
    taskQueuePrioInit(&(manager->waitingQueue), TASK_NUM, compareArrivalTime);
    taskQueueFIFOInit(&(manager->arrivedQueue));
}

void taskArrvAddTask(taskArrvManager *manager, struct myTCB *task) {
    taskQueuePrioEnqueue(&(manager->waitingQueue), task);
}

void taskArrvUpdate(taskArrvManager *manager) {
    while (!taskQueuePrioIsEmpty(&(manager->waitingQueue))) {
        struct myTCB *nextTask = taskQueuePrioPeek(&(manager->waitingQueue));
        if (nextTask->taskParam.arrivalTime <= systemTick) {
            taskQueuePrioDequeue(&(manager->waitingQueue));
            taskQueueFIFOEnqueue(&(manager->arrivedQueue), nextTask);
        } else {
            break;
        }
    }
}

struct myTCB *taskArrvGetNext(taskArrvManager *manager) {
    return taskQueueFIFODequeue(&(manager->arrivedQueue));
}

int taskArrvHasArrived(taskArrvManager *manager) {
    return !taskQueueFIFOIsEmpty(&(manager->arrivedQueue));
}
