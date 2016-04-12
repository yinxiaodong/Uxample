/****************************************************************************
* Copyright (C), www.gigadevice.com , HTOL-Program
* 使用内部8MHz时钟，PE14驱动LED间隔闪烁。
* 
* v0.1    2013-4-2 Felix Xu  初始版本
*
*/
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/****************************************************************************
* 名    称：int main(void)
* 功    能：主函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
int main(void)
{
	SysTick_Configuration();
	RCC_Config();
	GPIO_Config();
	EXTI1_Config();
	USART3_Config();

	while(1)	
	{
		printf("The microcontroller runs at %dMHz!\r\n",SystemCoreClock/1000000);
		LED_Spark();
		Delay_1ms(200);
	}



}




