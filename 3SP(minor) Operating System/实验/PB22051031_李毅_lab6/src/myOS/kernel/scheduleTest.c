#include "../include/task.h"
#include "../include/myPrintk.h"

/* 测试任务函数 */
void testTask1(void) {
    int i;
    for (i = 0; i < 3; i++) {
        myPrintk(0x3, "Task1 executing - iteration %d\n", i);
        // 简单的忙等待模拟任务执行
        volatile int j;
        for (j = 0; j < 100000; j++);
    }
    myPrintk(0x3, "Task1 completed\n");
}

void testTask2(void) {
    int i;
    for (i = 0; i < 2; i++) {
        myPrintk(0x4, "Task2 executing - iteration %d\n", i);
        volatile int j;
        for (j = 0; j < 150000; j++);
    }
    myPrintk(0x4, "Task2 completed\n");
}

void testTask3(void) {
    int i;
    for (i = 0; i < 4; i++) {
        myPrintk(0x5, "Task3 executing - iteration %d\n", i);
        volatile int j;
        for (j = 0; j < 80000; j++);
    }
    myPrintk(0x5, "Task3 completed\n");
}

void testTask4(void) {
    int i;
    for (i = 0; i < 1; i++) {
        myPrintk(0x6, "Task4 executing - iteration %d\n", i);
        volatile int j;
        for (j = 0; j < 200000; j++);
    }
    myPrintk(0x6, "Task4 completed\n");
}

/* 测试FCFS调度算法 */
void testFCFS(void) {
    myPrintk(0x2, "\n=== Testing FCFS Scheduling ===\n");
    setSchedulingAlgorithm(SCHED_FCFS, 0);
    
    createTestTask(testTask1, "Task1", 0, 10, 1);
    createTestTask(testTask2, "Task2", 1, 8, 2);
    createTestTask(testTask3, "Task3", 2, 6, 3);
    createTestTask(testTask4, "Task4", 3, 12, 1);
}

/* 测试SJF调度算法 */
void testSJF(void) {
    myPrintk(0x2, "\n=== Testing SJF Scheduling ===\n");
    setSchedulingAlgorithm(SCHED_SJF, 0);
    
    // 创建不同执行时间的任务来测试SJF
    createTestTask(testTask1, "Task1", 0, 10, 1);  // 长任务
    createTestTask(testTask2, "Task2", 1, 4, 2);   // 短任务
    createTestTask(testTask3, "Task3", 2, 6, 3);   // 中等任务
    createTestTask(testTask4, "Task4", 3, 2, 1);   // 最短任务
}

/* 测试优先级调度算法 */
void testPriority(void) {
    myPrintk(0x2, "\n=== Testing Priority Scheduling ===\n");
    setSchedulingAlgorithm(SCHED_PRIO, 0);
    
    // 创建不同优先级的任务（数值越小优先级越高）
    createTestTask(testTask1, "Task1", 0, 10, 3);  // 低优先级
    createTestTask(testTask2, "Task2", 1, 8, 1);   // 高优先级
    createTestTask(testTask3, "Task3", 2, 6, 2);   // 中优先级
    createTestTask(testTask4, "Task4", 3, 12, 1);  // 高优先级
}

/* 测试时间片轮转调度算法 */
void testRoundRobin(void) {
    myPrintk(0x2, "\n=== Testing Round Robin Scheduling (quantum=3) ===\n");
    setSchedulingAlgorithm(SCHED_RR, 3);
    
    createTestTask(testTask1, "Task1", 0, 10, 1);
    createTestTask(testTask2, "Task2", 1, 8, 2);
    createTestTask(testTask3, "Task3", 2, 6, 3);
}

/* 调度算法演示主函数 */
void scheduleDemo(void) {
    myPrintk(0x2, "Starting Scheduling Algorithm Demonstration\n");
    
    // 可以选择运行不同的测试
    // 注意：在实际使用中，一次只能运行一个测试
    
    // testFCFS();
    // testSJF(); 
    // testPriority();
    testRoundRobin();
    
    myPrintk(0x2, "Scheduling demonstration completed\n");
}
