/****************************************************************************
* Copyright (C), www.gigadevice.com , HTOL-Program
* ʹ���ڲ�8MHzʱ�ӣ�PE14����LED�����˸��
* 
* v0.1    2013-4-2 Felix Xu  ��ʼ�汾
*
*/
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/****************************************************************************
* ��    �ƣ�int main(void)
* ��    �ܣ�������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
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




