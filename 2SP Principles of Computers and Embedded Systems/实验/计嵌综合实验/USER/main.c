#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "12864.h"
#include <string.h>
extern int delaymode;
extern int delaytime;
extern char delaystring[16];
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);
	LED_Init();
	KEY0_Init();
	KEY1_Init();
	EXTI0_Init();
	EXTI1_Init();
	LCD_GPIO_Init();
	LCD_Init();
	LED0=1;
	strcpy(delaystring,"0100");
	LCD_Display_Words(0,0,"delaytime");
	LCD_Display_Words(1,0,(uint8_t*)delaystring);
	while(1)
	{
		LED0=!LED0;
		switch(delaymode)
		{
			case 0: delaytime=100;
			strcpy(delaystring,"0100");
			break;
		  case 1: delaytime=200;
			strcpy(delaystring,"0200");
			break;
			case 2: delaytime=500;
			strcpy(delaystring,"0500");
			break;
			case 3: delaytime=1000;
			strcpy(delaystring,"1000");
			break;
			case 4: delaytime=2000;
			strcpy(delaystring,"2000");
			break;
			default:delaytime=1000;
			strcpy(delaystring,"1000");
			break;
		}

		delay_ms(delaytime);
	}
}

//3.2
//#include "sys.h"
//#include "delay.h"
//#include "usart.h"
//#include "led.h"
//#include "pwm.h"

//int main(void)
//{
//	int pwm=0;
//	delay_init(168);
//	LED_Init();
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	TIM2_PWM_Init(3000,0);
//	
//	while(1)
//	{
//		delay_ms(1);
//		//修改比较值，修改占空比
//		if(pwm>3000)
//		{
//			pwm=0;
//		}
//		pwm++;
//		TIM_SetCompare3(TIM2, pwm); //pwm 即为 CCRx
//	}
//}


//3.1

//#include "sys.h"
//#include "delay.h"
//#include "usart.h"
//#include "led.h"
//#include "timer.h"
//int main(void)
//{
//	int arr=8191;
//	int psc=8191;
//	delay_init(168);	//初始化延时函数
//	LED_Init();
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组 2
//	TIM3_Init(arr,psc);//TIM3 初始化，参数计算后自行填写
//	while(1)
//	{
//		LED0=!LED0;
//		delay_ms(100);
//	}
//}