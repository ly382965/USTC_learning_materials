.globl start # 一般都用start
/*此处，按照multiboot协议要求定义必要的参数*/
/*格式：XXX_ITEM_NAME=value*/
/*value可以是十六进制的（0x开头）、十进制的等等*/

# TODO 补全下面三个参数
MAGIC_ITEM_NAME =    0x1BADB002
FLAGS_ITEM_NAME =    0x00000000
CHECKSUM_ITEM_NAME = -(MAGIC_ITEM_NAME + FLAGS_ITEM_NAME)

/*此处开始，按协议标准来定义必须的multiboot header*/

# TODO 将xxx自行修改为section的名字，利用定义好的参数，通过 .long 语句声明 Multiboot Header 的三个域
.section .multiboot
.align 4
    /*使用.long和前面定义的参数构建头结构，每次32位，格式为：.long XXX_ITEM_NAME*/
    .long MAGIC_ITEM_NAME     # 待补全 
    .long FLAGS_ITEM_NAME     # 待补全
    .long CHECKSUM_ITEM_NAME     # 待补全

.text # 进入代码段
.code32 # 32位代码

start: # 这个跟第一行的声明要一致
    /*下面屏幕输出OK或其他字符序列*/
    /*使用指令movl $0x12345678, 0xB8000*/ # 0x1234和0x5678各自输出1个字符
    /*根据需要输出多个字符，也可以使用其他mov指令*/
    /*可以根据需要使用nop指令隔开不同功能片段，也可以适当使用空行*/

    movl $0x2f652f48, 0xB8000   /* H e */
    movl $0x2f6c2f6c, 0xB8004   /* l l */
    movl $0x2f202f6f, 0xB8008   /* o   */
    movl $0x2f6f2f57, 0xB800C   /* W o */
    movl $0x2f6c2f72, 0xB8010   /* r l */
    movl $0x2f202f64, 0xB8014   /* d   */
    movl $0x2f422f50, 0xB8018   /* P B */
    movl $0x2f322f32, 0xB801C   /* 2 2 */
    movl $0x2f352f30, 0xB8020   /* 0 5 */
    movl $0x2f302f31, 0xB8024   /* 1 0 */
    movl $0x2f312f33, 0xB8028   /* 3 1 */
    movl $0x2f6c2f20, 0xB802C   /*   l */
    movl $0x2f792f69, 0xB8030   /* i y */
    movl $0x2f202f69, 0xB8034   /* i   */
    movl $0x2f202f20, 0xB8038   /*     */
    movl $0x2f202f20, 0xB803C   /*     */
    movl $0x2f202f20, 0xB8040   /*     */
    movl $0x2f202f20, 0xB8044   /*     */
    movl $0x2f202f20, 0xB8048   /*     */
    movl $0x2f202f20, 0xB804C   /*     */
    
    /*根据需要初始化串口*/
    /*根据需要串口输出你的字符序列，详见前面串口编程简介*/
    /* 初始化串口 */

    movw $0x3F8, %dx
    movb $0x50, %al  /* P */
    outb %al, %dx
    movb $0x42, %al  /* B */
    outb %al, %dx
    movb $0x32, %al  /* 2 */
    outb %al, %dx
    movb $0x32, %al  /* 2 */
    outb %al, %dx
    movb $0x30, %al  /* 0 */
    outb %al, %dx
    movb $0x35, %al  /* 5 */
    outb %al, %dx
    movb $0x31, %al  /* 1 */
    outb %al, %dx
    movb $0x30, %al  /* 0 */
    outb %al, %dx
    movb $0x33, %al  /* 3 */
    outb %al, %dx
    movb $0x31, %al  /* 1 */
    outb %al, %dx
    movb $0x20, %al  /* 空格 */
    outb %al, %dx
    movb $0x6C, %al  /* l */
    outb %al, %dx
    movb $0x69, %al  /* i */
    outb %al, %dx
    movb $0x79, %al  /* y */
    outb %al, %dx
    movb $0x69, %al  /* i */
    outb %al, %dx

/*实验结束，让计算机停机，方法：使用hlt指令，或者死循环*/
loop:   hlt
        jmp     loop
