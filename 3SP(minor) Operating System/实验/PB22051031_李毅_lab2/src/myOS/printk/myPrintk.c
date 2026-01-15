/*
 * 实现myPrint功能 先学习C语言的可变参数内容
 * 需要调用到格式化输出的function（vsprintf）
 */ 

// 不需要修改

#include <stdarg.h>

//NOTE:append2screen函数在./dev/vga.c中定义、实现

extern void append2screen(char *str,int color);

extern int vsprintf(char *buf, const char *fmt, va_list argptr);

char kBuf[400];
int myPrintk(int color,const char *format, ...){
	int count;
	
	va_list argptr;
	va_start(argptr,format);//初始化argptr
	
	count=vsprintf(kBuf,format,argptr);
	
	append2screen(kBuf,color);//VGA输出
	
	va_end(argptr);
	
	return count;
}

char uBuf[400];
int myPrintf(int color,const char *format, ...){
	int count;
	
	va_list argptr;
	va_start(argptr,format);//初始化argptr
	
	count=vsprintf(uBuf,format,argptr);
	
	append2screen(uBuf,color);//VGA输出
	
	va_end(argptr);
	
	return count;
}