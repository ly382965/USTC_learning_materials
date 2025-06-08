//T3
/*
#include "stm32f4xx.h"
int main(void)
{
	unsigned int ui_tmp;
	ui_tmp = __get_FAULTMASK(); //Get Fault Mask register
	ui_tmp = __get_BASEPRI(); //Get Base Priority register
	ui_tmp = __get_PRIMASK(); //Get Priority Mask Register
	ui_tmp = __get_CONTROL(); //Get CONTROL Register
	ui_tmp = __get_MSP(); //Get Main Stack Pointer
}
*/


//T2

int main(void)
{
	unsigned char uc_c=0x78;
	unsigned int amount_1=0;
	unsigned char test=0x01;
	while(test!=0x00)
	{
		if((uc_c & test) != 0x00)
		{
			amount_1++;
		}
		test=test<<1;
	}
}


//T1
/*
int main (void)
{
unsigned int ui_tmp;
unsigned int ui_a, ui_b, ui_c;
static int i_tmp; //signed int (32bits)
static short s16_tmp; //signed short (16bits)
static float f_tmp; //floating point (32bits)
static int s[8];
int k;
//????? IEEE754 ??????
f_tmp = -0.5;
f_tmp = f_tmp + 1;
	
//????,?? ui_tmp, ui_a, ui_b, ui_c ??????
//?????? PC ???

ui_a = 1;
ui_b = 2;
ui_c = 0xFF;
	
//????? PSR ??????? Negtive
ui_c = ui_a - ui_b;
ui_tmp = ui_c;
//????????(??)
i_tmp = -1;
i_tmp = i_tmp - 1;
s16_tmp = -1;
s16_tmp = -2;
s16_tmp = s16_tmp - 32766;
//?????????????
for(k=8; k>0; --k)
s[k-1] = 0x80000000 + k;
}
*/