//12864.c
#include "12864.h"
#include "delay.h"
void LCD_GPIO_Init()
{
  //GPIO 初始化代码
	GPIO_InitTypeDef  GPIO_InitStructure;   
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG|
								RCC_AHB1Periph_GPIOF, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOG,GPIO_Pin_1);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 |GPIO_Pin_14;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOF, GPIO_Pin_15 |GPIO_Pin_14); 
	
	CS=1;
	SID=1;
	SCLK=1;
}
void SendByte(u8 byte)
{
	u8 i;
	for(i = 0;i < 8;i++)
	{
		if((byte << i) & 0x80) //0x80(1000 0000)
		{
			SID = 1;
		}
		else
		{
			SID = 0;
		}
		SCLK = 0;
		delay_us(5);
		SCLK = 1;
	}
}
void Lcd_WriteCmd(u8 Cmd )
{
	delay_ms(1);
	SendByte(WRITE_CMD); //11111,RW(0),RS(0),0
	SendByte(0xf0&Cmd);
	SendByte(Cmd<<4);
}
void Lcd_WriteData(u8 Dat )
{
	delay_ms(1);
	SendByte(WRITE_DAT);
	SendByte(0xf0&Dat);
	SendByte(Dat<<4);
}
void LCD_Init(void)
{
	delay_ms(50);
	Lcd_WriteCmd(0x30);
	delay_ms(1);
	Lcd_WriteCmd(0x30);
	delay_ms(1);
	Lcd_WriteCmd(0x0c);
	delay_ms(1);
	Lcd_WriteCmd(0x01);
	delay_ms(30);
	Lcd_WriteCmd(0x06);
}
void LCD_Display_Words(uint8_t x,uint8_t y,uint8_t*str)
{
	Lcd_WriteCmd(LCD_addr[x][y]);
	while(*str>0)
	{
		Lcd_WriteData(*str);
		str++;
	}
}
void LCD_Clear(void)
{
	Lcd_WriteCmd(0x01);
	delay_ms(2);
}
