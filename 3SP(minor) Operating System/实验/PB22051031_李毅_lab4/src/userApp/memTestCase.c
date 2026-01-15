/* init.c */
#include "../myOS/userInterface.h"
#include "shell.h"

int testCase1(int argc, unsigned char **argv){  
	//======for malloc===============================
	char*buf1 = (char*)malloc(19);
	char*buf2 = (char*)malloc(24);

	for(int i=0;i<17;i++) *(buf1+i) = '*';
	*(buf1+17) = '\n';
	*(buf1+18) = '\000';

	for(int i=0;i<22;i++) *(buf2+i) = '#';
	*(buf2+22) = '\n';
	*(buf2+23) = '\000';

	myPrintf(0x5, "We allocated 2 buffers.\n");
	myPrintf(0x5, "BUF1(size=19, addr=0x%x) filled with 17(*): ",(unsigned long)buf1);
	myPrintf(0x7,buf1);
	myPrintf(0x5, "BUF2(size=24, addr=0x%x) filled with 22(#): ", (unsigned long)buf2);
	myPrintf(0x7,buf2);

	myPrintf(0x7,"\n");
	
	free((unsigned long)buf1);
	free((unsigned long)buf2);

	return 0;
}

int testCase2(int argc, unsigned char **argv){
	//======for malloc===============================
	char*buf1 = (char*)malloc(11);
	char*buf2 = (char*)malloc(21);

	for(int i=0;i<9;i++) *(buf1+i) = '+';
	*(buf1+9) = '\n';
	*(buf1+10) = '\000';

	for(int i=0;i<19;i++) *(buf2+i) = ',';
	*(buf2+19) = '\n';
	*(buf2+20) = '\000';

	myPrintf(0x5, "We allocated 2 buffers.\n");
	myPrintf(0x5, "BUF1(size=9, addr=0x%x) filled with 9(+): ",(unsigned long)buf1);
	myPrintf(0x7,buf1);
	myPrintf(0x5, "BUF2(size=19, addr=0x%x) filled with 19(,): ", (unsigned long)buf2);
	myPrintf(0x7,buf2);

	myPrintf(0x7,"\n");

	free((unsigned long)buf1);
	free((unsigned long)buf2);

	return 0;
}

int maxMallocSizeNow(int argc, unsigned char **argv){
	int i=0x1000;
	unsigned long x;

	while(1){
		x = malloc(i);
		if(x) free(x);	
		else break;

		i += 0x1000;
	}
	myPrintf(0x7, "MAX_MALLOC_SIZE: 0x%x (with step = 0x1000);\n",i);	
}

//======for dPartition===============================
int testdP1(int argc, unsigned char **argv){
	unsigned long x,x1,xHandler;
	int i, tsize = 0x100;
	x = malloc(tsize); 
	if (x){
		myPrintf(0x7, "We had successfully ");
		myPrintf(0x5, "malloc()");
		myPrintf(0x7, " a small memBlock (size=0x%x, addr=0x%x);\n", tsize,x);

		myPrintf(0x7, "It is initialized as a very small dPartition;\n");
		xHandler = dPartitionInit(x,tsize);
		dPartitionWalkByAddr(x);

		i=0x10;
		while(1){
			x1 = dPartitionAlloc(xHandler,i); 
			myPrintf(0x7, "Alloc a memBlock with size 0x%x, ", i);
			if(x1) {	
				myPrintf(0x5, "success(addr=0x%x)!",x1);
				dPartitionFree(xHandler,x1);
				myPrintf(0x7, "......Relaesed;\n");
			} else {
				myPrintf(0x5, "failed!\n");
				break;
			}
			
			i <<= 1;
		}

		myPrintf(0x7,"Now, converse the sequence.\n");
		while(i >= 0x10){
			x1 = dPartitionAlloc(xHandler,i); 
			myPrintf(0x7, "Alloc a memBlock with size 0x%x, ", i);
			if(x1) {	
				myPrintf(0x5, "success(addr=0x%x)!",x1);
				dPartitionFree(xHandler,x1);
				myPrintf(0x7, "......Relaesed;\n");
			} else myPrintf(0x5, "failed!\n");
			
			i >>= 1;
		}
		
		free(x);
	} else myPrintf(0x7,"MALLOC FAILED, CAN't TEST dPartition\n");	
}



int testdP2(int argc, unsigned char **argv){
	unsigned long x,x1,x2,x3,xHandler;
	int i, tsize = 0x100;
	x = malloc(tsize); 
	if (x){
		myPrintf(0x7, "We had successfully ");
		myPrintf(0x5, "malloc()");
		myPrintf(0x7, " a small memBlock (size=0x%x, addr=0x%x);\n", tsize,x);

		myPrintf(0x7, "It is initialized as a very small dPartition;\n");
		xHandler = dPartitionInit(x,tsize);
		dPartitionWalkByAddr(x);

		myPrintf(0x7,"Now, A:B:C:- ==> -:B:C:- ==> -:C- ==> - .\n");

		x1 = dPartitionAlloc(xHandler,0x10); 
		myPrintf(0x7, "Alloc memBlock A with size 0x10: ");
		if(x1) myPrintf(0x5, "success(addr=0x%x)!\n",x1);
		else myPrintf(0x5, "failed!\n");
		*(unsigned long*)x1 = 0xAAAAAAAA;		
		dPartitionWalkByAddr(xHandler);

		x2 = dPartitionAlloc(xHandler,0x20); 
		myPrintf(0x7, "Alloc memBlock B with size 0x20: ");
		if(x2) myPrintf(0x5, "success(addr=0x%x)!\n",x2);
		else myPrintf(0x5, "failed!\n");
		*(unsigned long*)x2 = 0xBBBBBBBB;		
		dPartitionWalkByAddr(xHandler);

		x3 = dPartitionAlloc(xHandler,0x30); 
		myPrintf(0x7, "Alloc memBlock C with size 0x30: ");
		if(x3) myPrintf(0x5, "success(addr=0x%x)!\n",x3);
		else myPrintf(0x5, "failed!\n");
		*(unsigned long*)x3 = 0xCCCCCCCC;		
		dPartitionWalkByAddr(xHandler);
		
		myPrintf(0x7,"Now, release A.\n");
		dPartitionFree(xHandler,x1); 
		dPartitionWalkByAddr(xHandler);
		
		myPrintf(0x7,"Now, release B.\n");
		dPartitionFree(xHandler,x2); 
		dPartitionWalkByAddr(xHandler);

		myPrintf(0x7,"At last, release C.\n");
		dPartitionFree(xHandler,x3); 
		dPartitionWalkByAddr(xHandler);
		
		free(x);
	} else myPrintf(0x7,"MALLOC FAILED, CAN't TEST dPartition\n");	
}

int testeFP(int argc, unsigned char **argv){
	unsigned long i=0x1000;//int
	unsigned long x,x1,x2,x3,x4,x5,xHandler;
	unsigned long psize = 31;//int
	unsigned long n = 4;//int
	unsigned long tsize;//int
	//======for eFPartition===============================
	
	tsize = eFPartitionTotalSize(psize,n);
	x = malloc(tsize); myPrintf(0x7,"X:0x%x:%d \n",x,tsize);
	if (x) {
		myPrintf(0x7, "We had successfully ");
		myPrintf(0x5, "malloc()");
		myPrintf(0x7, " a small memBlock (size=0x%x, addr=0x%x);\n", tsize,x);

		myPrintf(0x7, "It is initialized as a very small ePartition;\n");
		xHandler = eFPartitionInit(x,psize,n);

		eFPartitionWalkByAddr(xHandler);

		x1 = eFPartitionAlloc(xHandler);
		if(x1){
			*(unsigned long *)x1 = 0xAAAAAAAA;
			myPrintf(0x7,"Alloc memBlock A, start = 0x%x: 0x%x \n",x1,*(unsigned long *)x1);
		} else myPrintf(0x7,"Alloc memBlock A, failed!\n");
		eFPartitionWalkByAddr(xHandler);

		x2 = eFPartitionAlloc(xHandler);
		if(x2){
			*(unsigned long *)x2 = 0xBBBBBBBB;
			myPrintf(0x7,"Alloc memBlock B, start = 0x%x: 0x%x \n",x2,*(unsigned long *)x2);
		} else myPrintf(0x7,"Alloc memBlock B, failed!\n");
		eFPartitionWalkByAddr(xHandler);

		x3 = eFPartitionAlloc(xHandler);
		if(x3){
			*(unsigned long *)x3 = 0xCCCCCCCC;
			myPrintf(0x7,"Alloc memBlock C, start = 0x%x: 0x%x \n",x3,*(unsigned long *)x3);
		} else myPrintf(0x7,"Alloc memBlock C, failed!\n");
		eFPartitionWalkByAddr(xHandler);

		x4 = eFPartitionAlloc(xHandler);
		if(x4){
			*(unsigned long *)x4 = 0xDDDDDDDD;
			myPrintf(0x7,"Alloc memBlock D, start = 0x%x: 0x%x \n",x4,*(unsigned long *)x4);
		} else myPrintf(0x7,"Alloc memBlock D, failed!\n");
		eFPartitionWalkByAddr(xHandler);

		x5 = eFPartitionAlloc(xHandler);
		if(x5){
			*(unsigned long *)x5 = 0xEEEEEEEE;
			myPrintf(0x7,"Alloc memBlock E, start = 0x%x: 0x%x \n",x5,*(unsigned long *)x5);
		} else myPrintf(0x7,"Alloc memBlock E, failed!\n");
		eFPartitionWalkByAddr(xHandler);

		myPrintf(0x7,"Now, release A.\n");
		eFPartitionFree(xHandler,x1);
		eFPartitionWalkByAddr(xHandler);

		myPrintf(0x7,"Now, release B.\n");
		eFPartitionFree(xHandler,x2);
		eFPartitionWalkByAddr(xHandler);

		myPrintf(0x7,"Now, release C.\n");
		eFPartitionFree(xHandler,x3);
		eFPartitionWalkByAddr(xHandler);

		myPrintf(0x7,"Now, release D.\n");
		eFPartitionFree(xHandler,x4);		
		eFPartitionWalkByAddr(xHandler);
	} else myPrintf(0x7,"TSK2: MALLOC FAILED, CAN't TEST eFPartition\n");

	return 0;
}

int testdP3(int argc, unsigned char **argv){
	unsigned long x,x1,x2,x3,xHandler;
	int i, tsize = 0x100;
	x = malloc(tsize); 
	if (x){
		myPrintf(0x7, "We had successfully ");
		myPrintf(0x5, "malloc()");
		myPrintf(0x7, " a small memBlock (size=0x%x, addr=0x%x);\n", tsize,x);

		myPrintf(0x7, "It is initialized as a very small dPartition;\n");
		xHandler = dPartitionInit(x,tsize);
		dPartitionWalkByAddr(x);

		myPrintf(0x7,"Now, A:B:C:- ==> -:B:C:- ==> -:C- ==> - .\n");

		x1 = dPartitionAlloc(xHandler,0x10); 
		myPrintf(0x7, "Alloc memBlock A with size 0x10: ");
		if(x1) myPrintf(0x5, "success(addr=0x%x)!\n",x1);
		else myPrintf(0x5, "failed!\n");
		*(unsigned long*)x1 = 0xAAAAAAAA;		
		dPartitionWalkByAddr(xHandler);

		x2 = dPartitionAlloc(xHandler,0x20); 
		myPrintf(0x7, "Alloc memBlock B with size 0x20: ");
		if(x2) myPrintf(0x5, "success(addr=0x%x)!\n",x2);
		else myPrintf(0x5, "failed!\n");
		*(unsigned long*)x2 = 0xBBBBBBBB;		
		dPartitionWalkByAddr(xHandler);

		x3 = dPartitionAlloc(xHandler,0x30); 
		myPrintf(0x7, "Alloc memBlock C with size 0x30: ");
		if(x3) myPrintf(0x5, "success(addr=0x%x)!\n",x3);
		else myPrintf(0x5, "failed!\n");
		*(unsigned long*)x3 = 0xCCCCCCCC;		
		dPartitionWalkByAddr(xHandler);
		
		myPrintf(0x7,"At last, release C.\n");
		dPartitionFree(xHandler,x3); 
		dPartitionWalkByAddr(xHandler);

		myPrintf(0x7,"Now, release B.\n");
		dPartitionFree(xHandler,x2); 
		dPartitionWalkByAddr(xHandler);

		myPrintf(0x7,"Now, release A.\n");
		dPartitionFree(xHandler,x1); 
		dPartitionWalkByAddr(xHandler);
		
		free(x);
	} else myPrintf(0x7,"MALLOC FAILED, CAN't TEST dPartition\n");		
}

#define NULL (void*)0
void memTestCaseInit(void){	
	addNewCmd("testMalloc1\0", testCase1, NULL, "Malloc, write and read.\0");
	addNewCmd("testMalloc2\0", testCase2, NULL, "Malloc, write and read.\0");		
	addNewCmd("maxMallocSizeNow\0", maxMallocSizeNow, NULL, "MAX_MALLOC_SIZE always changes. What's the value Now?\0");

	addNewCmd("testdP1\0", testdP1, NULL, "Init a dPatition(size=0x100) [Alloc,Free]* with step = 0x20\0");
	addNewCmd("testdP2\0", testdP2, NULL, "Init a dPatition(size=0x100) A:B:C:- ==> -:B:C:- ==> -:C:- ==> - .\0");
	addNewCmd("testdP3\0", testdP3, NULL, "Init a dPatition(size=0x100) A:B:C:- ==> A:B:- ==> A:- ==> - .\0");
	
	addNewCmd("testeFP\0", testeFP, NULL, "Init a eFPatition. Alloc all and Free all.\0");
}
