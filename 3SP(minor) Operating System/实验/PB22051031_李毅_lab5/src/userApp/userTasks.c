#define WHITE 0x7
extern void tskEnd(void);
extern int createTsk(void (*tskBody)(void));
extern int myPrintf(int color,const char *format, ...);

char *message1 = "********************************\n";

void myTsk0(void){      
	myPrintf(WHITE, message1);
	myPrintf(WHITE, "*     Tsk0: HELLO WORLD!       *\n");
	myPrintf(WHITE, message1);
	
	tskEnd();   //the task is end
}

void myTsk1(void){
	myPrintf(WHITE, message1);
	myPrintf(WHITE, "*     Tsk1: HELLO WORLD!       *\n");
	myPrintf(WHITE, message1);
	
	tskEnd();   //the task is end
}

void myTsk2(void){
	myPrintf(WHITE, message1);
	myPrintf(WHITE, "*     Tsk2: HELLO WORLD!       *\n");
	myPrintf(WHITE, message1);
	
	tskEnd();  //the task is end
}
