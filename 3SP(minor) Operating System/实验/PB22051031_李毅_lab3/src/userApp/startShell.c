#include "io.h"
#include "myPrintk.h"
#include "uart.h"
#include "vga.h"
#include "i8253.h"
#include "i8259A.h"
#include "tick.h"
#include "wallClock.h"
//NOTE:你可以自行定义辅助函数来帮助你实现
typedef struct myCommand {
    char name[80];
    char help_content[200];
    int (*func)(int argc, char (*argv)[8]);
}myCommand; 

// Forward‐declare command functions
static int func_cmd(int argc, char (*argv)[8]);
static int func_help(int argc, char (*argv)[8]);

myCommand cmd={"cmd\0","List all command\n\0",func_cmd};
myCommand help={"help\0","Usage: help [command]\n\0Display info about [command]\n\0",func_help};

static myCommand *commands[] = { &cmd, &help };
static const int cmd_count = 2;

int strcmp(char *a,char *b){
    while((*a==*b)&&*a!='\0'){a++;b++;}
    return *a-*b;
}

int func_cmd(int argc, char (*argv)[8]){
    int i;
    myPrintk(0x07, "Supported commands:\n");
    for (i = 0; i < cmd_count; i++)
    {
        // 列出命令名及简介
        uart_put_chars(commands[i]->name);
        uart_put_char('\n');
        append2screen(commands[i]->name, 0x07);
        append2screen("\n", 0x07);
    }
    return 0;
} 

int func_help(int argc, char (*argv)[8]) {
    int i;
    if (argc == 1) 
    {  
        // show help for all commands
        for (i = 0; i < cmd_count; i++) 
        {
            if (strcmp(commands[i]->name, "help") == 0) 
            {
                uart_put_chars(commands[i]->help_content);
                uart_put_char('\n');
                append2screen(commands[i]->help_content, 0x07);
                append2screen("\n", 0x07);
                return 0;
            }
        }
    } 
    else 
    {
        // show help for argv[1]
        for (i = 0; i < cmd_count; i++) {
            if (strcmp(argv[1], commands[i]->name) == 0) 
            {
                uart_put_chars(commands[i]->help_content);
                uart_put_char('\n');
                append2screen(commands[i]->help_content, 0x07);
                append2screen("\n", 0x07);
                return 0;
            }
        }
        append2screen("no help\n", 0x07);
    }
    return 0;
}


void startShell(void){
    //我们通过串口来实现数据的输入
    char BUF[256]; //输入缓存区
    int BUF_len=0;	//输入缓存区的长度

    int argc;
    char argv[8][8];

    do{
        BUF_len=0; 
        myPrintk(0x07,"Student>>\0");
        while((BUF[BUF_len]=uart_get_char())!='\r'){
            uart_put_char(BUF[BUF_len]);//将串口输入的数存入BUF数组中
            BUF_len++;  //BUF数组的长度加
        }
        uart_put_chars(" -pseudo_terminal\0");
        uart_put_char('\n');
        // TODO: 你需要填写它
        //OK,助教已经帮助你们实现了“从串口中读取数据存储到BUF数组中”的任务，接下来你们要做
        //的就是对BUF数组中存储的数据进行处理(也即，从BUF数组中提取相应的argc和argv参
        //数)，再根据argc和argv，寻找相应的myCommand ***实例，进行***.func(argc,argv)函数
        //调用。

        //比如BUF中的内容为 “help cmd”
        //那么此时的argc为2 argv[0]为help argv[1]为cmd
        //接下来就是 help.func(argc, argv)进行函数调用即可

        // 解析 BUF 到 argv
        argc = 0;
        int idx = 0;
        while (idx < BUF_len)
        {
            // 跳过空格
            while (idx < BUF_len && BUF[idx] == ' ') idx++;

            if (idx >= BUF_len) break;
            int arg_len = 0;
            // 读取一个单词，不超过 7 个字符
            while (idx < BUF_len && BUF[idx] != ' ' && arg_len < 7)
            {
                argv[argc][arg_len++] = BUF[idx++];
            }
            argv[argc][arg_len] = '\0';
            // 跳过单词剩余字符
            while (idx < BUF_len && BUF[idx] != ' ') idx++;
            argc++;
            if (argc >= 8) break;
        }

        // 调用命令
        if (argc > 0) {
            int i;
            for (i = 0; i < cmd_count; i++)
            {
                if (strcmp(argv[0], commands[i]->name) == 0) 
                {
                    commands[i]->func(argc, argv);
                    break;
                }
            }
            if (i == cmd_count) 
            {
                uart_put_chars("Unknown command: ");
                uart_put_chars(argv[0]);
                uart_put_char('\n');
                append2screen("Unknown command\n", 0x07);
                append2screen(argv[0], 0x07);
                append2screen("\n", 0x07);
            }
        }

    }while(1);

}

