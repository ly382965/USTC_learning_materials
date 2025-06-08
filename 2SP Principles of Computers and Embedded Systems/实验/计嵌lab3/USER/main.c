//T4

#include "sys.h"
#include "delay.h"
#include "usart.h"

#include "12864.h"
int main()
{
	delay_init(168);
	LCD_GPIO_Init();
	LCD_Init();
	while(1)
	{
	  //LCD_Display_Picture(ImageData);
	  delay_ms(2000);
		LCD_Display_Words(0,0,"红");
		LCD_Display_Words(1,0,"实");
		LCD_Display_Words(2,0,"交");
		LCD_Display_Words(3,0,"融");
	}
}

//T3

//#include "stm32f4xx.h"
//#include "delay.h"//延时函数所在的头文件
//#include "sys.h"

//void LED_Init(void); 		

//#define ON   Bit_SET     //GPIO的布尔变量，用于GPIO_WriteBit函数
//#define OFF  Bit_RESET   //GPIO的布尔变量，用于GPIO_WriteBit函数

//#define LED0(x)  GPIO_WriteBit(GPIOG, GPIO_Pin_11, x)//写IO口状态，0/1
//#define LED1(x)  GPIO_WriteBit(GPIOG, GPIO_Pin_10, x)
//#define LED2(x)  GPIO_WriteBit(GPIOG, GPIO_Pin_9, x)
//#define LED3(x)  GPIO_WriteBit(GPIOD, GPIO_Pin_7, x)
//#define LED4(x)  GPIO_WriteBit(GPIOG, GPIO_Pin_3, x)
//#define LED5(x)  GPIO_WriteBit(GPIOG, GPIO_Pin_2, x)
//#define LED6(x)  GPIO_WriteBit(GPIOD, GPIO_Pin_13, x)
//#define LED7(x)  GPIO_WriteBit(GPIOD, GPIO_Pin_12, x)

//int main(void)
//{ 
//	LED_Init();		       //初始化LED端口
//	delay_init(168);     //初始化延时函数

//	while(1)
//	{
//		if(PEin(4)==1)
//		{
//			PDout(12)=1;PDout(13)=1;PGout(2)=1;PGout(3)=1;PDout(7)=1;PGout(9)=1;PGout(10)=1;PGout(11)=1;
//		}
//		else
//		{
//			PDout(12)=0;PDout(13)=0;PGout(2)=0;PGout(3)=0;PDout(7)=0;PGout(9)=0;PGout(10)=0;PGout(11)=0;
//		}
//		delay_ms(50);
////		PDout(12)=1;delay_ms(500);PDout(12)=0;delay_ms(500);//7
////		PDout(13)=1;delay_ms(500);PDout(13)=0;delay_ms(500);//6
////		PGout(2)=1;delay_ms(500);PGout(2)=0;delay_ms(500);//5
////		PGout(3)=1;delay_ms(500);PGout(3)=0;delay_ms(500);//4
////		PDout(7)=1;delay_ms(500);PDout(7)=0;delay_ms(500);//3
////		PGout(9)=1;delay_ms(500);PGout(9)=0;delay_ms(500);//2
////		PGout(10)=1;delay_ms(500);PGout(10)=0;delay_ms(500);//1
////		PGout(11)=1;delay_ms(500);PGout(11)=0;delay_ms(500);//0
////		PGout(10)=1;delay_ms(500);PGout(10)=0;delay_ms(500);//1
////		PGout(9)=1;delay_ms(500);PGout(9)=0;delay_ms(500);//2
////		PDout(7)=1;delay_ms(500);PDout(7)=0;delay_ms(500);//3
////		PGout(3)=1;delay_ms(500);PGout(3)=0;delay_ms(500);//4
////		PGout(2)=1;delay_ms(500);PGout(2)=0;delay_ms(500);//5
////		PDout(13)=1;delay_ms(500);PDout(13)=0;delay_ms(500);//6
//		
//		/*流水灯显示*/
////		LED0(ON);delay_ms(500);LED0(OFF);delay_ms(500);
////		LED1(ON);delay_ms(500);LED1(OFF);delay_ms(500);
////		LED2(ON);delay_ms(500);LED2(OFF);delay_ms(500);
////		LED3(ON);delay_ms(500);LED3(OFF);delay_ms(500);
////		LED4(ON);delay_ms(500);LED4(OFF);delay_ms(500);
////		LED5(ON);delay_ms(500);LED5(OFF);delay_ms(500);
////		LED6(ON);delay_ms(500);LED6(OFF);delay_ms(500);
////		LED7(ON);delay_ms(500);LED7(OFF);delay_ms(500);      
// 	}
//}

//void LED_Init(void)
//{    	 
//  GPIO_InitTypeDef  GPIO_InitStructure;   //GPIO初始化结构体
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG|
//								RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOG、GPIOD时钟 开GPIO RCC_AHB1Periph_GPIOD 看define

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_9 | GPIO_Pin_2 | GPIO_Pin_3;				 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOG, &GPIO_InitStructure);
//	GPIO_ResetBits(GPIOG,GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_2 | GPIO_Pin_3);//LED1,LED2,LED3,LED4,LED5

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 |GPIO_Pin_12 | GPIO_Pin_13;				 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOD, &GPIO_InitStructure);
//	GPIO_ResetBits(GPIOD, GPIO_Pin_7 |GPIO_Pin_12|GPIO_Pin_13);  //LED6,LED7		 
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;			 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//输入
//  //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOE, &GPIO_InitStructure);
//	GPIO_ResetBits(GPIOE, GPIO_Pin_4);  //DIP0
//}

