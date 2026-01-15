.text
.code32 

#上下文切换
#上下文示意图：
#（高地址）CS：IP
#（低地址）
  .global CTX_SW
CTX_SW:  
	pushf
	pusha

	movl prevTSK_StackPtr, %eax
	movl %esp, (%eax)
	movl nextTSK_StackPtr, %esp

	popa 
	popf
	ret
