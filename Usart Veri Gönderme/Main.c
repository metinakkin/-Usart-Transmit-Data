#include "stm32f4xx.h"                  // Device header
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char str[50];
uint32_t i;
void USART_Puts(USART_TypeDef* USARTx,volatile char *s) // char karakter sayisi kadar döndürüyor
{
 while(*s)
 {
  while(!(USARTx ->SR & 0x00000040));
	 USART_SendData(USARTx,*s);
	 *s++;
 }	 
}	



int main()
{
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); // transmitter tx A2 GPIOya bagli usartta
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; //Alternatif fonksiyonlar(input,output,adc disinda baska sey oldugu)
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);//USARTtan bilgiyi GPIOya atacaz,CPUya tanitmamiz lazim
	
	USART_InitStructure.USART_BaudRate=115200; // Saniye içinde hat üzerinden kaç tane bit gönderilmesi gerektigi
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART2,&USART_InitStructure);
	USART_Cmd(USART2,ENABLE);
	
	while(1)
	{
	  sprintf(str, "Metin \n");
		USART_Puts(USART2,str);
		i=600000;
		while(i)
			i--;
	}	
	
	
	
}	
	
