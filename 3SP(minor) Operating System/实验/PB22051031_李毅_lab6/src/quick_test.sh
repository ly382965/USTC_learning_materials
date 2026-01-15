#!/bin/bash

# 快速调度算法测试脚本
# 使用方法: ./quick_test.sh [fcfs|sjf|rr]

ALGORITHM=${1:-fcfs}

echo "========================================"
echo "快速调度算法测试 - $ALGORITHM"
echo "========================================"

# 检查目录
if [ ! -f "Makefile" ]; then
    echo "错误：请在src目录下运行此脚本"
    exit 1
fi

# 备份原始文件
if [ ! -f "userApp/main.c.backup" ]; then
    cp userApp/main.c userApp/main.c.backup
    echo "备份原始main.c"
fi

# 设置测试参数
case $ALGORITHM in
    fcfs)
        DEFINE_FLAG="TEST_FCFS"
        ALG_NAME="FCFS (先来先服务)"
        ;;
    sjf)
        DEFINE_FLAG="TEST_SJF"
        ALG_NAME="SJF (最短作业优先)"
        ;;
    rr)
        DEFINE_FLAG="TEST_RR"
        ALG_NAME="RR (时间片轮转)"
        ;;
    *)
        echo "用法: $0 [fcfs|sjf|rr]"
        echo "默认使用fcfs"
        DEFINE_FLAG="TEST_FCFS"
        ALG_NAME="FCFS (先来先服务)"
        ;;
esac

echo "测试算法: $ALG_NAME"

# 准备测试文件
cp userApp/scheduleTestMain.c userApp/main.c
sed -i "1i#define $DEFINE_FLAG" userApp/main.c

# 编译
echo "正在编译..."
make clean > /dev/null 2>&1
make > compile.log 2>&1

if [ $? -ne 0 ]; then
    echo "编译失败！"
    cat compile.log
    # 恢复文件
    cp userApp/main.c.backup userApp/main.c
    exit 1
fi

echo "编译成功！"
echo "启动测试 (按Ctrl+C停止)..."
echo ""

# 运行测试
qemu-system-i386 -kernel output/myOS.elf -serial stdio -display none

# 恢复原始文件
echo ""
echo "恢复原始文件..."
cp userApp/main.c.backup userApp/main.c
rm userApp/main.c.backup

echo "测试完成！"
