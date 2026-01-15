.text
.code32
_start:
	.globl enable_interrupt
enable_interrupt:
# TODO 你需要填写它
	sti
	ret
	
	.globl disable_interrupt
disable_interrupt:
# TODO 你需要填写它
	cli
	ret
