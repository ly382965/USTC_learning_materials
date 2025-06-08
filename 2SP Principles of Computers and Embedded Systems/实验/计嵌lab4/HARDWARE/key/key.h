#include "stm32f4xx.h"
#include "delay.h"
#include "sys.h"

void KEY_Init(void); 		

#define ON   Bit_SET     
#define OFF  Bit_RESET   

#define KEY PEin(0)
/*
#define LED0(x)  GPIO_WriteBit(GPIOG, GPIO_Pin_11, x)//Ð´IO¿Ú×´Ì¬£¬0/1
#define LED1(x)  GPIO_WriteBit(GPIOG, GPIO_Pin_10, x)
#define LED2(x)  GPIO_WriteBit(GPIOG, GPIO_Pin_9, x)
#define LED3(x)  GPIO_WriteBit(GPIOD, GPIO_Pin_7, x)
#define LED4(x)  GPIO_WriteBit(GPIOG, GPIO_Pin_3, x)
#define LED5(x)  GPIO_WriteBit(GPIOG, GPIO_Pin_2, x)
#define LED6(x)  GPIO_WriteBit(GPIOD, GPIO_Pin_13, x)
#define LED7(x)  GPIO_WriteBit(GPIOD, GPIO_Pin_12, x)
*/
