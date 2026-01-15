#include "../myOS/userInterface.h"
#include "../myOS/include/scheduleTest.h"
#include "../myOS/include/task.h"

/* 测试用的简单任务 */
void simpleTask1(void) {
    int i;
    for (i = 0; i < 10; i++) {  /* 增加迭代次数 */
        myPrintf(0x3, "Task1[%d] ", i);
        // 模拟CPU密集型任务，增加延迟让时间片更容易观察
        volatile int j;
        for (j = 0; j < 1000000; j++);  /* 增加延迟 */
    }
    myPrintf(0x3, "Task1 END\n");
    tskEnd();
}

void simpleTask2(void) {
    int i;
    for (i = 0; i < 8; i++) {  /* 增加迭代次数 */
        myPrintf(0x4, "Task2[%d] ", i);
        volatile int j;
        for (j = 0; j < 1000000; j++);  /* 增加延迟 */
    }
    myPrintf(0x4, "Task2 END\n");
    tskEnd();
}

void simpleTask3(void) {
    int i;
    for (i = 0; i < 6; i++) {  /* 增加迭代次数 */
        myPrintf(0x5, "Task3[%d] ", i);
        volatile int j;
        for (j = 0; j < 1000000; j++);  /* 增加延迟 */
    }
    myPrintf(0x5, "Task3 END\n");
    tskEnd();
}

void simpleTask4(void) {
    int i;
    for (i = 0; i < 2; i++) {
        myPrintf(0x6, "Task4[%d] ", i);
        volatile int j;
        for (j = 0; j < 1000000; j++);
    }
    myPrintf(0x6, "Task4 END\n");
    tskEnd();
}

/* FCFS调度测试 */
void testFCFSScheduling(void) {
    myPrintf(0x2, "\n=== FCFS Scheduling Test ===\n");
    setSchedulingAlgorithm(SCHED_FCFS, 0);
    
    // 按顺序创建任务
    createTestTask(simpleTask1, "Task1", 0, 10, 1);
    createTestTask(simpleTask2, "Task2", 0, 8, 2);  
    createTestTask(simpleTask3, "Task3", 0, 6, 3);
    
    myPrintf(0x2, "FCFS tasks created, execution order should be: Task1 -> Task2 -> Task3\n");
}

/* SJF调度测试 */
void testSJFScheduling(void) {
    myPrintf(0x2, "\n=== SJF Scheduling Test ===\n");
    setSchedulingAlgorithm(SCHED_SJF, 0);
    
    // 创建不同执行时间的任务，SJF应该按执行时间从短到长排序
    createTestTask(simpleTask1, "Task1", 0, 10, 1);  // 长任务
    createTestTask(simpleTask2, "Task2", 0, 4, 2);   // 短任务
    createTestTask(simpleTask3, "Task3", 0, 6, 3);   // 中等任务
    createTestTask(simpleTask4, "Task4", 0, 2, 1);   // 最短任务
    
    myPrintf(0x2, "SJF tasks created, execution order should be: Task4(2) -> Task2(4) -> Task3(6) -> Task1(10)\n");
}

/* RR调度测试 */
void testRRScheduling(void) {
    myPrintf(0x2, "\n=== Round Robin Scheduling Test (quantum=3) ===\n");
    setSchedulingAlgorithm(SCHED_RR, 3);
    
    // 创建几个任务进行时间片轮转
    createTestTask(simpleTask1, "Task1", 0, 10, 1);
    createTestTask(simpleTask2, "Task2", 0, 8, 2);
    createTestTask(simpleTask3, "Task3", 0, 6, 3);
    
    myPrintf(0x2, "RR tasks created, should see interleaved execution with time quantum=3\n");
}

/* 调度算法演示主函数 */
void myMain(void) {
    clear_screen();
    
    myPrintf(0x07, "********************************\n");
    myPrintf(0x07, "*    SCHEDULING ALGORITHM      *\n");
    myPrintf(0x07, "*         DEMO PROGRAM         *\n");
    myPrintf(0x07, "********************************\n");
    
    // 可以通过修改这里来测试不同的调度算法
    // 注意：一次只能运行一种调度算法测试
    
    #ifdef TEST_FCFS
    testFCFSScheduling();
    #elif defined(TEST_SJF)
    testSJFScheduling();
    #elif defined(TEST_RR)
    testRRScheduling();
    #else
    // 默认测试FCFS
    testFCFSScheduling();
    #endif
    
    tskEnd();
}
