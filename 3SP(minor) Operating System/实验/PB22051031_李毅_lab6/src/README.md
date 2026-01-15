# 调度算法测试工具使用说明

本项目实现了三种经典的进程调度算法：FCFS、SJF、RR，并提供了完整的测试工具。

## 文件结构

### 核心模块
- `taskPara.c/h` - 任务参数模块，管理任务的到达时间、执行时间、优先级等
- `taskQueue.c/h` - 任务队列数据结构（FIFO队列和优先队列）
- `taskArrv.c/h` - 任务到达模块，基于系统时钟管理任务到达
- `schedulers.c/h` - 具体调度算法实现（FCFS、SJF、优先级、RR）
- `scheduler.c/h` - 调度器抽象接口，统一各种调度算法
- `scheduleTest.c/h` - 调度算法测试用例
- `task.c/h` - 更新后的任务管理器，集成新调度系统

### 测试工具
- `interactive_test.sh` - 交互式测试脚本（推荐）
- `quick_test.sh` - 快速测试脚本
- `test_schedulers.sh` - 自动化测试脚本
- `scheduleTestMain.c` - 专门的测试主程序

## 使用方法

### 1. 交互式测试（推荐）
```bash
cd src
./interactive_test.sh
```

选择菜单选项：
- 1) FCFS - 先来先服务调度
- 2) SJF - 最短作业优先调度  
- 3) RR - 时间片轮转调度
- 4) 自动测试所有算法
- 5) 退出

### 2. 快速测试特定算法
```bash
cd src
./quick_test.sh fcfs    # 测试FCFS
./quick_test.sh sjf     # 测试SJF
./quick_test.sh rr      # 测试RR
```

### 3. 自动化测试所有算法
```bash
cd src
./test_schedulers.sh
```

## 调度算法说明

### FCFS (First Come First Served)
- **特点**: 先到先服务，非抢占式
- **优点**: 实现简单，公平
- **缺点**: 平均等待时间较长
- **测试现象**: 任务按创建顺序依次执行

### SJF (Shortest Job First)  
- **特点**: 最短作业优先，非抢占式
- **优点**: 平均等待时间最短
- **缺点**: 可能导致长作业饥饿
- **测试现象**: 执行时间短的任务优先执行

### RR (Round Robin)
- **特点**: 时间片轮转，抢占式
- **优点**: 响应时间好，适合交互式系统
- **缺点**: 时间片选择影响性能
- **测试现象**: 任务交替执行，每次执行一个时间片

## 测试任务说明

测试程序创建了4个不同特征的任务：
- **Task1**: 执行时间10，优先级1（长任务）
- **Task2**: 执行时间4，优先级2（短任务）  
- **Task3**: 执行时间6，优先级3（中等任务）
- **Task4**: 执行时间2，优先级1（最短任务）

## 预期测试结果

### FCFS测试
执行顺序：Task1 → Task2 → Task3 → Task4

### SJF测试  
执行顺序：Task4(2) → Task2(4) → Task3(6) → Task1(10)

### RR测试（时间片=3）
交替执行：Task1[0-2] → Task2[0-2] → Task3[0-2] → Task1[3-5] → ...

## 注意事项

1. **编译依赖**: 确保已安装qemu-system-i386
2. **目录要求**: 必须在src目录下运行测试脚本
3. **文件备份**: 脚本会自动备份和恢复原始main.c文件
4. **停止测试**: 按Ctrl+C可以随时停止测试
5. **测试时长**: 每个测试默认运行10-20秒

## 故障排除

1. **编译失败**: 检查Makefile中是否包含所有新模块
2. **运行异常**: 确保qemu-system-i386已正确安装
3. **权限问题**: 确保测试脚本有执行权限（chmod +x）
4. **路径错误**: 确保在src目录下运行脚本

## 扩展开发

要添加新的调度算法：
1. 在`schedulers.h/c`中实现新算法
2. 在`scheduler.h`中添加新的`schedType`枚举
3. 更新`scheduler.c`中的switch语句
4. 在`scheduleTest.c`中添加对应测试

要修改测试参数：
1. 编辑`scheduleTestMain.c`中的任务参数
2. 修改时间片大小、任务数量等参数
