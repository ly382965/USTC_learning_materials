.globl start

MAGIC_ITEM_NAME =    0x1BADB002
FLAGS_ITEM_NAME =    0x00000000
CHECKSUM_ITEM_NAME = -(MAGIC_ITEM_NAME + FLAGS_ITEM_NAME)

.section .multiboot
.align 4
    .long MAGIC_ITEM_NAME     
    .long FLAGS_ITEM_NAME     
    .long CHECKSUM_ITEM_NAME     

.text 
.code32 

start:
  call _start

loop:   hlt
        jmp     loop
