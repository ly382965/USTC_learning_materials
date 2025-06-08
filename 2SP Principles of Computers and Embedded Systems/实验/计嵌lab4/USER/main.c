//4
//#include "sys.h"
//#include "delay.h"
//#include "usart.h"
//#include "led.h"
//#include "key.h"
//#include "exti.h"
//int main(void)
//{
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	delay_init(168);
//	LED_Init();
//	KEY_Init();
//	EXTIX_Init();
//	LED0=1;
//	while(1)
//	{
//		
//	}
//}

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

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
int main(void)
{
	int arr=8191;
	int psc=8191;
	delay_init(168);	//初始化延时函数
	LED_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组 2
	TIM3_Init(arr,psc);//TIM3 初始化，参数计算后自行填写
	while(1)
	{
		LED0=!LED0;
		delay_ms(100);
	}
}