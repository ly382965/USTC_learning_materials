#include "key.h"

void KEY_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;   //GPIO³õÊ¼»¯½á¹¹Ìå
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//Ê¹ÄÜGPIOG¡¢GPIODÊ±ÖÓ

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//ÊäÈë
  //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOE, GPIO_Pin_0);  //DIP0	 
}

