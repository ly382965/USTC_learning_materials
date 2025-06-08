#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "12864.h"
#include <string.h>

extern u16 USART_TX_EN;
extern u8 USART_RX_BUF[USART_REC_LEN];
extern u16 USART_RX_STA;
	
int main()
{
	char USART_SendBuf[]="Hello!";
	int i;
	int Len=strlen(USART_SendBuf);
	int Row=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);
	LCD_GPIO_Init();
	LCD_Init();
	uart_init(115200);
	//
	
	while(1)
	{
		//LCD_Display_Words(0,0,"ok");
		delay_ms(1000);
		if(USART_TX_EN)
		{
			for(i=0;i<Len;i++)
			{
				USART_SendData(USART1, USART_SendBuf[i]);
				while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)!=SET);
			}
			USART_TX_EN=0;
		}
		
		if(USART_RX_STA==Len)
		{
			LCD_Display_Words(Row,0,USART_RX_BUF);
			Row++;
			USART_RX_STA=0;
			if(Row==5)
			{
				Row=0;
				LCD_Clear();
			}
			USART_TX_EN=1;
		}
	}
	
}
