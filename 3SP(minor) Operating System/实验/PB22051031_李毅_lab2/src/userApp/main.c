/* 
 * 请确保以下的代码可以原封不动的成功编译和执行
 * 助教测试时会替换相应的参数
 * 不需要修改
 */
extern int myPrintf(int color,const char *format, ...);
extern int myPrintk(int color,const char *format, ...);

void myMain(void){    
    int i;
	/*NOTE:用户使用myPrintf而不使用myPrink接口*/
	myPrintf(0x7,"main\n");
	for (i=1;i<30;i++) myPrintf(i,"%d\n",i);
	myPrintf(0x7,"asildhasdjlkasjdl;kasjdl;asjd;ljasld;jasl;djasl;djakfhiowhvfsjf;klasjcl;sdjpofajsdofjsd;lfk123456789\n");
	myPrintf(0x7,"liyiPB22051031\n");
	return;
}
