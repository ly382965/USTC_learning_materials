/*
 * 本文件实现vga的相关功能，清屏和屏幕输出
 * clear_screen和append2screen必须按照如下借口实现
 * 可以增加其他函数供clear_screen和append2screen调用
 */
extern void outb (unsigned short int port_to, unsigned char value);
extern unsigned char inb(unsigned short int port_from);

//VGA字符界面规格：25行80列
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

//VGA显存初始地址为0xB8000

short cur_line = 0;
short cur_column = 0;//当前光标位置
char * vga_init_p = (char *)0xB8000;
char * vga_current_p = (char *)0xB8000;

/*

*不必局限于以下框架，可以自定义接口来实现，只需要保证append2screen接口能够
被正确调用即可  

*/
void update_pointer(void){
	vga_current_p = vga_init_p + (cur_line * VGA_WIDTH + cur_column) * 2;
}

void update_cursor(void){//通过当前行值cur_cline与列值cur_column回写光标

	
	unsigned short position = cur_line * VGA_WIDTH + cur_column;

    outb(0x3D4, (unsigned char)0xE); // 写入高 8 位
    outb(0x3D5, (unsigned char)((position >> 8) & 0xFF));

    outb(0x3D4, (unsigned char)0xF); // 写入低 8 位
    outb(0x3D5, (unsigned char)(position & 0xFF));
}

void scroll_screen(void){//屏幕向上滚动一行

	for(int i=0 ; i< (VGA_HEIGHT-1) * VGA_WIDTH ; i++)
	{
		*(vga_init_p + i * 2) = *(vga_init_p + (i + VGA_WIDTH) * 2);
		*(vga_init_p + i * 2 + 1) = *(vga_init_p + (i + VGA_WIDTH) * 2 + 1);
	}
	for(int i=0 ; i< VGA_WIDTH ; i++)
	{
		*(vga_init_p + (VGA_HEIGHT - 1) * VGA_WIDTH * 2 + i * 2) = ' ';
		*(vga_init_p + (VGA_HEIGHT - 1) * VGA_WIDTH * 2 + i * 2 + 1) = 0x07;
	}
	update_cursor();
}

void clear_screen(void) {//清屏
	for(int i=0 ; i< VGA_HEIGHT * VGA_WIDTH ; i++)
	{
		*(vga_init_p + i * 2) = ' ';
		*(vga_init_p + i * 2 + 1) = 0x07;
	}
	cur_line = 0;
	cur_column = 0;
	update_cursor();
	update_pointer();
}

void append2screen(char *str,int color){ //将str输出到vga屏幕
	int i = 0;
	while(str[i] != '\0')
	{
		if(str[i] == '\n') //换行
		{
			cur_line++ ;
			cur_column = 0;
		}
		else
		{
			*(vga_current_p) = str[i];
			*(vga_current_p + 1) = color;
			cur_column++;
		}
		if(cur_column >= VGA_WIDTH) //换行
		{
			cur_line++;
			cur_column = 0;
		}
		if(cur_line >= VGA_HEIGHT) //滚屏
		{
			scroll_screen();
			cur_line--;
			cur_column = 0;
		}
		i++;
		update_cursor();
		update_pointer();
	}
}


